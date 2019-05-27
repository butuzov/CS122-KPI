DELIMITER $$

DROP PROCEDURE IF EXISTS sp_01_DoctorsBySpeciality $$

CREATE PROCEDURE sp_01_DoctorsBySpeciality( 
    IN  VAR_SEARCH   VARCHAR(255), 
    IN  VAR_FACULITY INT, 
    OUT VAR_RECORDS  INT) 
exit_point:BEGIN

        -- Optional Variables
        IF VAR_FACULITY <= 0 THEN 
            SELECT NULL INTO VAR_FACULITY; 
        END IF;
        
        -- Creating Temporary table for storing results.
        CREATE TEMPORARY TABLE `temporary_DoctorsBySpeciality`  (
            ID INT(11)
        ) ENGINE=MEMORY; 
        
        -- Performing Heavy Selection.
        INSERT INTO `temporary_DoctorsBySpeciality` SELECT w.ID FROM `workers` w
        WHERE w.ID IN (
            SELECT wf.WorkerID FROM `workers_facilities` wf
            JOIN workers_specialities ws ON ( 
                wf.WorkerID = ws.WorkerID AND ws.SpecialityID IN (
                    SELECT s.ID FROM `speciality` s 
                    WHERE lower(s.Speciality) LIKE CONCAT('%', VAR_SEARCH , '%')
                        AND s.Type = 'Medical' 
                )
            )
            WHERE wf.Status = 'Active' 
                AND wf.Type = 'Medical'
                AND wf.FacilityID in (
                    SELECT ID FROM `facilities`
                    WHERE ( ID = IFNULL( VAR_FACULITY, ID ) 
                        OR ParentID = IFNULL( VAR_FACULITY, ParentID ) 
                    ) 
            )
        );

        -- Saving Number of Found results.
        SELECT COUNT(*) FROM `temporary_DoctorsBySpeciality` INTO VAR_RECORDS;
        
        -- And Displaying Statment Results.
        IF VAR_RECORDS > 0 THEN
            SELECT `Name` FROM `workers` w WHERE w.ID IN (
                SELECT tmp.ID FROM `temporary_DoctorsBySpeciality` tmp
            );  
        END IF;

        -- Clean Up Results.
        DROP TABLE `temporary_DoctorsBySpeciality`;
    END $$
DELIMITER ;
 

 -- EXAMPLES

-- 01 Select Every Doctor that has speciality "Реаниматология" and 
-- works at institution with ID 1
CALL sp_01_DoctorsBySpeciality( "Реаниматология", 1, @TOTALRECORDS );
SELECT @TOTALRECORDS as "Rows Found";

-- 02 Select Every Doctor that has speciality "Реаниматология" and 
-- search for it globaly
CALL sp_01_DoctorsBySpeciality( "Реаниматология", NULL, @TOTALRECORDS );
SELECT @TOTALRECORDS as "Rows Found";

-- 03  Same as Above but providing negative value 
CALL sp_01_DoctorsBySpeciality( "Реаниматология", 0, @TOTALRECORDS );
SELECT @TOTALRECORDS as "Rows Found";