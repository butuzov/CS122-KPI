DELIMITER $$

DROP PROCEDURE IF EXISTS sd_14_AverageExaminations $$

CREATE PROCEDURE sd_14_AverageExaminations (
    VAR_LABORATORY INT,
    VAR_FACILITY   INT,
    VAR_DATE_START DATE, 
    VAR_DATE_END   DATE
)  
exit_point:BEGIN

        IF DATE(VAR_DATE_END) <= DATE(VAR_DATE_START) THEN
            SELECT "EXPECTING WIDER PERIOD; ABORT THIS MISSION";
            LEAVE exit_point;
        END IF; 

        SELECT COUNT(*) / TIMESTAMPDIFF(DAY, VAR_DATE_START, VAR_DATE_END) as AVG_EXAMINATIONS_PER_DAY
        FROM `laboratory_examinations` le
        WHERE le.LaboratoryID = VAR_LABORATORY
        AND le.Date BETWEEN DATE( VAR_DATE_START ) AND DATE( VAR_DATE_END )
        AND le.FacilityID in (
            SELECT ID FROM `facilities`
            WHERE ( ID = IFNULL( VAR_FACILITY, ID ) 
                OR ParentID = IFNULL( VAR_FACILITY, ParentID ) )
        );

    END $$
DELIMITER ;

CALL sd_14_AverageExaminations(21, 1, "2016-01-01", "2017-01-01");