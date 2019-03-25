DELIMITER $$

DROP PROCEDURE IF EXISTS sp_03_OperationsPerformedBy $$

CREATE PROCEDURE sp_03_OperationsPerformedBy ( 
    IN VAR_SEARCH VARCHAR(255), 
    IN VAR_LIMIT INT, 
    IN VAR_FACILITY INT, 
    OUT VAR_RECORDS INT
) 
exit_point:BEGIN

        -- Validating Requied Variables.
        IF VAR_LIMIT < 0 THEN 
            SELECT "EXPECTING LIMIT => 0; ABORT THIS MISSION";
            SELECT 0 INTO VAR_RECORDS;
            LEAVE exit_point;
        END IF;

        -- Optional Variables
        IF VAR_FACILITY <= 0 THEN 
            SELECT NULL INTO VAR_FACILITY; 
        END IF;
        
        -- Creating Temporary table for storing results.
        CREATE TEMPORARY TABLE `temporary_OperationsPerformedBy`  (
            ID INT(11)
        ) ENGINE=MEMORY; 
        
        -- Performing Heavy Selection.
        INSERT INTO `temporary_OperationsPerformedBy` 
        SELECT sd.WorkerID
        FROM `surgeries` s, `surgeries_doctors` sd
        WHERE s.FacilityID IN (
            SELECT ID FROM `facilities`
            WHERE ID = IFNULL(VAR_FACILITY, ID) 
                OR ParentID = IFNULL(VAR_FACILITY, ParentID)
        ) AND sd.WorkerID IN (
            SELECT WorkerID FROM `workers_specialities` ws 
            WHERE  sd.WorkerID = ws.WorkerID AND ws.SpecialityID IN (
                SELECT s.ID FROM `speciality` s 
                WHERE 
                LOWER(s.Speciality) LIKE CONCAT('%', VAR_SEARCH, '%')
                    AND s.Type = 'Medical' 
            )
        ) AND s.ID = sd.SurgeryID 
        GROUP BY sd.WorkerID HAVING count(*) > VAR_LIMIT;

        -- Saving Number of Found results.
        SELECT COUNT(*) FROM `temporary_OperationsPerformedBy` 
        INTO VAR_RECORDS;
        
        -- And Displaying Statment Results.
        IF VAR_RECORDS > 0 THEN
            SELECT `Name` FROM workers w WHERE w.ID IN (
                SELECT tmp.ID FROM `temporary_OperationsPerformedBy` tmp
            );  
        END IF;

        -- Clean Up Results.
        DROP TABLE `temporary_OperationsPerformedBy`;
    END $$
DELIMITER ;

-- Usage:
--  sp_03_OperationsPerformedBy( 
--      string:Profile, 
--      int: OperationsLimit,
--      int|null: FacilityID,
--      outgoing int: @found_rows
--  )
-- Use Next Examples for reference
-- Example One: Profile "Педиатрия", minimum 10 operations
CALL sp_03_OperationsPerformedBy("Педиатрия", 10, 0, @r);
SELECT CONCAT_WS(" ", "Found", @r, "Surgeon(s)") as Message;

-- Example Two: Profile "Педиатрия", minimum 10 operations, facility id 2.
CALL sp_03_OperationsPerformedBy("Педиатрия", 10, 1, @r);
SELECT CONCAT_WS(" ", "Found", @r, "Surgeon(s)") as Message;