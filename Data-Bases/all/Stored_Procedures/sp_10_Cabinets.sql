DELIMITER $$

DROP PROCEDURE IF EXISTS sp_10_Cabinets $$

CREATE PROCEDURE sp_10_Cabinets( 
    IN  VAR_DATE_START   DATE,
    IN  VAR_DATE_END     DATE,
    IN  VAR_FACILITY     INT,
    OUT VAR_RECORDS      INT
) 
exit_point:BEGIN

        -- Validating Requied Variables.
        IF VAR_FACILITY < 0 THEN 
            SELECT "EXPECTING LIMIT => 0; ABORT THIS MISSION"; 
            SELECT 0 INTO VAR_RECORDS;
            LEAVE exit_point;
        END IF;

        IF DATE(VAR_DATE_END) <= DATE(VAR_DATE_START) THEN
            SELECT "EXPECTING WIDER PERIOD; ABORT THIS MISSION";
            SELECT 0 INTO VAR_RECORDS;
            LEAVE exit_point;
        END IF;     

        -- Actual Selection
        SELECT SQL_CALC_FOUND_ROWS 
            fr.Number as Total_Cabinets,  
            SUM(tmp.Visits) as Total_VIsits
        FROM (
        SELECT  fr.ID, IFNULL(r.SignIn, '000-00-00') as Date, IF(r.SignIn IS NULL, 0, count(*)) as Visits
            FROM facilities_rooms fr
            LEFT JOIN registry r ON ( 
               fr.ID = r.RoomID 
                AND r.SignIn BETWEEN VAR_DATE_START AND VAR_DATE_END  
            )
            WHERE fr.FacilityID = VAR_FACILITY AND fr.Type = 'Cabinet'
            GROUP BY fr.ID, r.SignIn
        ) AS tmp
        JOIN facilities_rooms fr ON (tmp.ID = fr.ID )
        GROUP BY tmp.ID;

        -- Results.
        SELECT IFNULL(FOUND_ROWS(), 0) INTO VAR_RECORDS;
        
    END $$
DELIMITER ;
 

CALL sp_10_Cabinets("2019-01-01", "2019-03-01", 3, @TOTAL_ROWS);
SELECT @TOTAL_ROWS as "Всього Кабінетів";


CALL sp_10_Cabinets("2019-01-01", "2018-03-01", 3, @TOTAL_ROWS);
SELECT @TOTAL_ROWS as "Всього Кабінетів";