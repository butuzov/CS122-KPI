DELIMITER $$
DROP PROCEDURE IF EXISTS sp_07_StationaryPatients$$

CREATE PROCEDURE sp_07_StationaryPatients( 
    IN VAR_FACILITY   INT, 
    IN VAR_DOCTOR     INT, 
    IN VAR_DATE_START DATE, 
    IN VAR_DATE_END   DATE) 
exit_point:BEGIN
        DECLARE RESULTS INT DEFAULT 0; 

        -- Optional Variables
        IF VAR_FACILITY < 0 THEN 
            SELECT NULL INTO VAR_FACILITY; 
        END IF;

        IF VAR_DOCTOR <= 0 THEN 
            SELECT NULL INTO VAR_DOCTOR; 
        END IF;

        -- Validating Requied Variables.
        if (VAR_FACILITY IS NULL AND VAR_DOCTOR IS NULL) OR 
           (VAR_FACILITY IS NOT NULL AND VAR_DOCTOR IS NOT NULL) THEN 
            SELECT "EXPECTING FACILITY OR DOCTOR, NOT BOTH, NOT NONE; ABORT THIS MISSION";
            LEAVE exit_point;
        END IF;

        IF DATE(VAR_DATE_END) <= DATE(VAR_DATE_START) THEN
            SELECT "EXPECTING WIDER PERIOD; ABORT THIS MISSION";
            LEAVE exit_point;
        END IF; 
      

        -- Creating Temporary table for storing results.
        CREATE TEMPORARY TABLE `temporary__StationaryPatients`  (
            ID INT(11)
        ) ENGINE=MEMORY; 
        
        -- Performing Heavy Selection.
        INSERT INTO `temporary__StationaryPatients` 
        SELECT r.PatientID FROM registry r
        WHERE  r.Type = 'Stationary'
        AND ( r.SignIn >= VAR_DATE_START AND r.SignOut <= VAR_DATE_END )
        AND ( FacilityID = IFNULL(VAR_FACILITY, -1)
        OR  DoctorID = IFNULL(VAR_DOCTOR, -1) );

        -- Saving Number of Found results.
        SELECT COUNT(*) FROM `temporary__StationaryPatients` INTO RESULTS;
        
        -- And Displaying Statment Results.
        IF RESULTS > 0 THEN
            SELECT `Name` FROM `patients` p WHERE p.ID IN (
                SELECT tmp.ID FROM `temporary__StationaryPatients` tmp
            ); 
        END IF;

        -- Clean Up Results.
        DROP TABLE `temporary__StationaryPatients`;
    END $$
DELIMITER ;


-- OK 
CALL sp_07_StationaryPatients(1, null, '2004-01-01', '2004-04-01');
CALL sp_07_StationaryPatients(null, 4, '2004-01-01', '2004-04-01');

-- Bad
CALL sp_07_StationaryPatients(1, 4, '2004-01-01', '2004-04-01');
CALL sp_07_StationaryPatients(null, null, '2004-01-01', '2004-04-01');
CALL sp_07_StationaryPatients(null, 4, '2004-04-01', '2004-01-01');