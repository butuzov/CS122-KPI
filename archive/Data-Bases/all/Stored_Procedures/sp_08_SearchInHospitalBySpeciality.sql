DELIMITER $$

DROP PROCEDURE IF EXISTS sp_08_SearchInHospitalBySpeciality$$

CREATE PROCEDURE sp_08_SearchInHospitalBySpeciality( 
    IN  VAR_FACILITY INT,
    IN  VAR_SEARCH   VARCHAR(255)
)
exit_point:BEGIN
        DECLARE RESULTS INT DEFAULT 0; 

        -- Validating Requied Variables.
        IF VAR_FACILITY <= 0 THEN 
            SELECT "EXPECTING FACILITY TO BE PROVIDED > ; ABORT THIS MISSION";
            LEAVE exit_point;
        END IF;

        -- Optional Variables
        IF VAR_FACILITY <= 0 THEN 
            SELECT NULL INTO VAR_FACILITY; 
        END IF;
        
        -- Creating Temporary table for storing results.
        CREATE TEMPORARY TABLE `temporary__SearchInHospitalBySpeciality`  (
            ID INT(11)
        ) ENGINE=MEMORY; 
        
        -- Performing Heavy Selection.
        INSERT INTO `temporary__SearchInHospitalBySpeciality` 
        SELECT r.PatientID  FROM registry r 
        WHERE r.DoctorID IN (
            SELECT f.WorkerID FROM workers_facilities f 
            WHERE f.FacilityID = VAR_FACILITY
            AND f.WorkerID in (
                SELECT ws.WorkerID FROM `workers_specialities` ws 
                WHERE  ws.SpecialityID IN (
                    SELECT s.ID FROM `speciality` s 
                    WHERE LOWER(s.Speciality) LIKE CONCAT('%', VAR_SEARCH, '%')
                    AND s.Type = 'Medical' 
                )
            )
            AND f.Status = 'Active'
        ) 
        AND r.FacilityID = VAR_FACILITY
        AND r.Type IN ('Ambulatory','Stationary','Periodic');

        -- Saving Number of Found results.
        SELECT COUNT(*) FROM `temporary__SearchInHospitalBySpeciality` INTO RESULTS;
        
        -- And Displaying Statment Results.
        IF RESULTS > 0 THEN
             SELECT `Name` FROM `patients` p WHERE p.ID IN (
                SELECT tmp.ID FROM `temporary__SearchInHospitalBySpeciality` tmp
            );  
        END IF;

        -- Clean Up Results.
        DROP TABLE `temporary__SearchInHospitalBySpeciality`;
    END $$
DELIMITER ;

CALL sp_08_SearchInHospitalBySpeciality(1, "Дерматология");
CALL sp_08_SearchInHospitalBySpeciality(3, "Кардиология");