DELIMITER $$

DROP PROCEDURE IF EXISTS sp_13_SurgeryPatients $$

CREATE PROCEDURE sp_13_SurgeryPatients (
    IN  DATE_BEGIN   DATE,
    IN  DATE_END     DATE,
    IN  VAR_DOCTOR   INT, 
    IN  VAR_FACILITY INT, 
    OUT VAR_RECORDS  INT
) 
exit_point:BEGIN

        -- Validating Requied Variables.
        IF VAR_FACILITY > 0 AND VAR_DOCTOR > 0 THEN 
            SELECT "EXPECTING FACILITY OR DOCTOR <= 0; ABORT THIS MISSION";
            SELECT 0 INTO VAR_RECORDS;
            LEAVE exit_point;
        END IF;

        IF DATE(DATE_END) <= DATE(DATE_BEGIN) THEN
            SELECT "EXPECTING WIDER PERIOD; ABORT THIS MISSION";
            SELECT 0 INTO VAR_RECORDS;
            LEAVE exit_point;
        END IF; 

        -- Optional Variables
       IF VAR_FACILITY <= 0 THEN 
            SELECT NULL INTO VAR_FACILITY; 
        END IF;

        IF VAR_DOCTOR <= 0 THEN 
            SELECT NULL INTO VAR_DOCTOR; 
        END IF;
        
        -- Step 2: Validating Required Variables After Normalization
        IF VAR_FACILITY IS NULL AND VAR_DOCTOR IS NULL THEN 
            SELECT "EXPECTING FACILITY OR DOCTOR > 0; ABORT THIS MISSION";
            SELECT 0 INTO VAR_RECORDS;
            LEAVE exit_point;
        END IF;

        -- Creating Temporary table for storing results.
        CREATE TEMPORARY TABLE `temporary_SurgeryPatients`  (
            ID INT(11)
        ) ENGINE=MEMORY; 
        
        -- Performing Heavy Selection.
        INSERT INTO `temporary_SurgeryPatients` 
        SELECT p.ID FROM `patients` p 
        WHERE p.ID IN (
            SELECT s.PatientID FROM `surgeries` s, `surgeries_doctors` sd
            WHERE s.ID = sd.SurgeryID 
            AND DATE(s.Date) BETWEEN DATE( DATE_BEGIN ) AND DATE( DATE_END )
            AND ( sd.WorkerID = VAR_DOCTOR OR s.FacilityID IN (
                    SELECT ID FROM `facilities`
                    WHERE ( ID = VAR_FACILITY OR ParentID = VAR_FACILITY )
                ) 
            )   
        );
        
        -- Saving Number of Found results.
        SELECT COUNT(*) FROM `temporary_SurgeryPatients` INTO VAR_RECORDS;
        
        -- And Displaying Statment Results.
        IF VAR_RECORDS > 0 THEN
            SELECT `Name` FROM `patients` p WHERE p.ID IN (
                SELECT tmp.ID FROM `temporary_SurgeryPatients` tmp
            );  
        END IF;

        -- Clean Up Results.
        DROP TABLE `temporary_SurgeryPatients`;
    END $$
DELIMITER ;

-- General Usage:

-- Use Next Examples for reference
-- Example One: Profile "Педиатрия", minimum 10 operations
-- CALL sp_13_SurgeryPatients('1990-10-11', '2018-10-11', 0, 1, @R);
-- SELECT CONCAT_WS(" ", "Found", @r, "Patient(s)") as Message;

-- Example Two: Profile "Педиатрия", minimum 10 operations, facility id 2.
CALL sp_13_SurgeryPatients('2001-09-10', '2001-09-12', 1, 0, @R);
SELECT CONCAT_WS(" ", "Found", @r, "Patient(s)") as Message;
