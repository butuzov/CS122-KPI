DELIMITER $$

DROP PROCEDURE IF EXISTS sp_12_FamilyDoctor $$

CREATE PROCEDURE sp_12_FamilyDoctor( 
    IN  VAR_DOCTOR       INT,  
    IN  VAR_FACILITY     INT, 
    IN  VAR_SEARCH       VARCHAR(255)
) 
exit_point:BEGIN
        DECLARE RESULTS INT DEFAULT 0; 
        DECLARE SEARCH_EMPTY INT DEFAULT 0; 

        -- NULLING and Validating SQL.
        IF VAR_DOCTOR <= 0 THEN 
            SELECT NULL INTO VAR_DOCTOR; 
        END IF;
 
        IF VAR_FACILITY <= 0 THEN 
            SELECT NULL INTO VAR_FACILITY; 
        END IF;

        SELECT VAR_SEARCH = "" INTO SEARCH_EMPTY;

         -- Creating Temporary table for storing results.
        CREATE TEMPORARY TABLE IF NOT EXISTS `temporary__FamilyDoctor`  (
            ID INT(11)
        ) ENGINE=MEMORY; 


         -- Performing Heavy Selection.
        IF VAR_DOCTOR > 0 THEN
            
            INSERT INTO `temporary__FamilyDoctor` VALUES (VAR_DOCTOR);
        
        ELSEIF VAR_FACILITY > 0 THEN

            INSERT INTO `temporary__FamilyDoctor` 
            SELECT DoctorID FROM registry 
            WHERE FacilityID = VAR_FACILITY GROUP BY DoctorID;

        ELSEIF SEARCH_EMPTY = 0 THEN

            INSERT INTO `temporary__FamilyDoctor`
            SELECT wf.WorkerID FROM `workers_facilities` wf
            JOIN workers_specialities ws ON ( 
                wf.WorkerID = ws.WorkerID AND ws.SpecialityID IN (
                    SELECT s.ID FROM `speciality` s 
                    WHERE LOWER(s.Speciality) LIKE CONCAT('%', VAR_SEARCH,'%') 
                    AND s.Type = 'Medical' 
                )
            ) AND wf.Status = 'Active';

        ELSE
        
            SELECT "NO VALID INPUT VARS PROVIDED; ABORT THIS MISSION";
            LEAVE exit_point;

        END IF;

        -- Saving Number of Found results.
        SELECT COUNT(*) FROM `temporary__FamilyDoctor` INTO RESULTS;
        
        -- And Displaying Statment Results.
        IF RESULTS > 0 THEN
            SELECT count(PerDay) FROM (
                SELECT DoctorID, SignIn, count(*) as PerDay FROM registry r
                WHERE r.Type IN ( 'Periodic', 'Ambulatory', 'Stationary' ) 
                AND r.SignIn > DATE_SUB(NOW(), INTERVAL 2 WEEK)
                AND r.DoctorID IN (
                    SELECT tmp.ID FROM `temporary__FamilyDoctor` tmp
                )
                GROUP BY r.DoctorID ASC, r.SignIn DESC
            ) as r;
        END IF; 
    END $$
DELIMITER ;
 
CALL sp_12_FamilyDoctor( 1, 0, "");
CALL sp_12_FamilyDoctor( 1, NULL, "");


CALL sp_12_FamilyDoctor( 0, 1, "");
CALL sp_12_FamilyDoctor( NULL, 1, "");

CALL sp_12_FamilyDoctor( 0, 0, "Вертебрология");
CALL sp_12_FamilyDoctor( 0, 0, "Кардиология");

-- Fail
CALL sp_12_FamilyDoctor( 0, 0, "");
CALL sp_12_FamilyDoctor( NULL, 0, "");