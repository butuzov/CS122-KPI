DELIMITER $$

DROP PROCEDURE IF EXISTS sp_05_AcademicTitle $$

CREATE PROCEDURE sp_05_AcademicTitle ( 
    IN  VAR_SEARCH  VARCHAR(255), 
    IN  VAR_FACILITY INT, 
    OUT VAR_RECORDS INT
) 
exit_point:BEGIN

        -- Optional Variables
        IF VAR_FACILITY <= 0 THEN 
            SELECT NULL INTO VAR_FACILITY; 
        END IF;
        
        -- Creating Temporary table for storing results.
        CREATE TEMPORARY TABLE `temporary_AcademicTitle`  (
            ID INT(11)
        ) ENGINE=MEMORY; 
        
        -- Performing Heavy Selection.
        INSERT INTO `temporary_AcademicTitle` SELECT w.ID FROM `workers` w 
        WHERE w.ID IN (
            SELECT wf.WorkerID FROM `workers_facilities` wf
            JOIN workers_titles wt ON ( 
                    wt.WorkerID = wf.WorkerID 
                AND wt.Type = 'Academic' 
                AND wt.Title LIKE CONCAT('%', VAR_SEARCH, '%') 
            ) WHERE wf.Status = 'Active' 
                AND wf.Type = 'Medical'
                AND wf.FacilityID in (
                    SELECT ID FROM `facilities`
                    WHERE ID = IFNULL( VAR_FACILITY,ID ) 
                        OR ParentID = IFNULL( VAR_FACILITY,ParentID )
                )
        );

        -- Saving Number of Found results.
        SELECT COUNT(*) FROM `temporary_AcademicTitle` INTO VAR_RECORDS;
        
        -- And Displaying Statment Results.
        IF VAR_RECORDS > 0 THEN
            SELECT `Name` FROM `workers` w WHERE w.ID IN (
                SELECT tmp.ID FROM `temporary_AcademicTitle` tmp
            );  
        END IF;

        -- Clean Up Results.
        DROP TABLE `temporary_AcademicTitle`;

    END $$
DELIMITER ;
 
CALL sp_05_AcademicTitle("Доктор медицинских наук", 0, @TOTALRECORDS );
SELECT @TOTALRECORDS as "Rows Found";


CALL sp_05_AcademicTitle("Кандидат медицинских наук", 2, @TOTALRECORDS );
SELECT @TOTALRECORDS as "Rows Found";