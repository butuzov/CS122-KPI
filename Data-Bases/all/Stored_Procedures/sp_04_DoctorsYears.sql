DELIMITER $$

DROP PROCEDURE IF EXISTS sp_04_DoctorsYears $$

CREATE PROCEDURE sp_04_DoctorsYears( 
    IN  VAR_SEARCH   VARCHAR(255), 
    IN  VAR_YEARS    INT, 
    IN  VAR_FACILITY INT, 
    OUT VAR_RECORDS  INT
) 
exit_point:BEGIN

        -- Validating Requied Variables.
        IF VAR_YEARS < 0 THEN 
            SELECT "EXPECTING TOTAL_YEARS > 0; ABORT THIS MISSION";
            SELECT 0 INTO VAR_RECORDS;
            LEAVE exit_point;
        END IF;

        -- Optional Variables
        IF VAR_FACILITY <= 0 THEN 
            SELECT NULL INTO VAR_FACILITY; 
        END IF;
        
        -- Creating Temporary table for storing results.
        CREATE TEMPORARY TABLE `temporary_DoctorsYears`  (
            ID    INT(11),
            Years INT (2)
        ) ENGINE=MEMORY; 
        
        -- Performing Heavy Selection.
        INSERT INTO `temporary_DoctorsYears` 
        SELECT wf.WorkerID,  MAX(TIMESTAMPDIFF(YEAR, Start, CURDATE())) as Years 
            FROM `workers_facilities` wf 
            JOIN workers w ON ( w.ID = wf.WorkerID )
            JOIN workers_specialities ws ON ( ws.WorkerID =  w.ID AND  
                ws.SpecialityID IN (
                    SELECT s.ID FROM `speciality` s 
                    WHERE LOWER(s.Speciality) LIKE LOWER(CONCAT('%', VAR_SEARCH ,'%')) 
                    AND s.Type = 'Medical' 
                )
            )
            WHERE TIMESTAMPDIFF(YEAR, wf.Start, CURDATE()) > VAR_YEARS
                AND wf.Type = 'Medical'
                AND wf.Status = 'Active' 
                AND wf.FacilityID in (
                    SELECT ID FROM `facilities`
                    WHERE (
                        ID = IFNULL(VAR_FACILITY,ID) 
                        OR ParentID = IFNULL(VAR_FACILITY,ParentID)
                    )
            ) GROUP BY w.ID;

        -- Saving Number of Found results.
        SELECT COUNT(*) FROM `temporary_DoctorsYears` INTO VAR_RECORDS;
        
        -- And Displaying Statment Results.
        IF VAR_RECORDS > 0 THEN
            SELECT `Name` FROM `workers` w WHERE w.ID IN (
                SELECT tmp.ID FROM `temporary_DoctorsYears` tmp
            );  
        END IF;

        -- Clean Up Results.
        DROP TABLE `temporary_DoctorsYears`;
    END $$
DELIMITER ;

Call sp_04_DoctorsYears("Кардиология", 0, 1, @TOTALRECORDS );
SELECT @TOTALRECORDS as "Rows Found";


Call sp_04_DoctorsYears("Кардиология", -1, 1, @TOTALRECORDS );
SELECT @TOTALRECORDS as "Rows Found";