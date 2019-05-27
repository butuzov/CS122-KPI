DELIMITER $$

DROP PROCEDURE IF EXISTS sp_02_StaffBySpeciality $$

CREATE PROCEDURE sp_02_StaffBySpeciality( 
    IN  VAR_SEARCH   VARCHAR(255), 
    IN  VAR_FACULITY INT, 
    OUT VAR_RECORDS  INT) 
exit_point:BEGIN

        -- Optional Variables
        IF VAR_FACULITY <= 0 THEN 
            SELECT NULL INTO VAR_FACULITY; 
        END IF;
        
        -- Creating Temporary table for storing results.
        CREATE TEMPORARY TABLE `temporary_StaffBySpeciality`  (
            ID INT(11)
        ) ENGINE=MEMORY; 
        
        -- Performing Heavy Selection.
        INSERT INTO `temporary_StaffBySpeciality` 
        SELECT w.ID FROM `workers` w, `workers_facilities` wf
        WHERE w.ID = wf.WorkerID 
        AND wf.Status = 'Active' 
        AND wf.Type != 'Medical' 
        AND wf.Role LIKE CONCAT( '%', VAR_SEARCH, '%')
        AND wf.FacilityID IN (
            SELECT ID FROM `facilities`
            WHERE (
                ID = IFNULL(VAR_FACULITY,ID) 
                OR ParentID = IFNULL(VAR_FACULITY,ParentID)
            ) 
        );

        -- Saving Number of Found results.
        SELECT COUNT(*) FROM `temporary_StaffBySpeciality` INTO VAR_RECORDS;
        
        -- And Displaying Statment Results.
        IF VAR_RECORDS > 0 THEN
            SELECT `Name` FROM `workers` w WHERE w.ID IN (
                SELECT tmp.ID FROM `temporary_StaffBySpeciality` tmp
            );  
        END IF;

        -- Clean Up Results.
        DROP TABLE `temporary_StaffBySpeciality`;
    END $$
DELIMITER ;
 
 -- 01 Select Every Staff Personal that has role "Охрана" and 
-- works at institution with ID 1
CALL sp_02_StaffBySpeciality( "Охрана", 1, @TOTALRECORDS );
SELECT @TOTALRECORDS as "Rows Found";

-- 02 Select Every Staff Personal speciality "Администратор" and 
-- search for it globaly
CALL sp_02_StaffBySpeciality( "Администратор", NULL, @TOTALRECORDS );
SELECT @TOTALRECORDS as "Rows Found";

-- 03  Same as Above but providing negative value 
CALL sp_02_StaffBySpeciality( "Администратор", 0, @TOTALRECORDS );
SELECT @TOTALRECORDS as "Rows Found";

-- 02 Select Every Staff Personal speciality "Прибиральниця" and 
-- search for it in Helthcare institution with id 3
CALL sp_02_StaffBySpeciality( "Прибиральниця", 3, @TOTALRECORDS );
SELECT @TOTALRECORDS as "Rows Found";