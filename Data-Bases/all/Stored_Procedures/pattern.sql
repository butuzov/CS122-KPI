DELIMITER $$

DROP PROCEDURE IF EXISTS sp_NN___REPLACE_TABLE_NAME__ $$

CREATE PROCEDURE sp_NN___REPLACE_TABLE_NAME__( 
    IN  VAR_SEARCH   VARCHAR(255), 
    IN  VAR_LIMIT    INT, 
    IN  VAR_FACILITY INT, 
    OUT VAR_RECORDS  INT) 
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
        CREATE TEMPORARY TABLE `__REPLACE_TABLE_NAME__`  (
            ID INT(11)
        ) ENGINE=MEMORY; 
        
        -- Performing Heavy Selection.
        INSERT INTO `__REPLACE_TABLE_NAME__` SELECT w.ID FROM `workers` w;

        -- Saving Number of Found results.
        SELECT COUNT(*) FROM `__REPLACE_TABLE_NAME__` INTO VAR_RECORDS;
        
        -- And Displaying Statment Results.
        IF VAR_RECORDS > 0 THEN
            SELECT `Name` FROM `workers` w WHERE w.ID IN (
                SELECT tmp.ID FROM `__REPLACE_TABLE_NAME__` tmp
            );  
        END IF;

        -- Clean Up Results.
        DROP TABLE `__REPLACE_TABLE_NAME__`;
    END $$
DELIMITER ;
 