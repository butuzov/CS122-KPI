SET @VAR_FACILITY = 1;
SET @VAR_LAB = 21;
SET @DATE_BEGIN = "2016-01-01";
SET @DATE_END = DATE_ADD(@DATE_BEGIN, INTERVAL 1 YEAR);

SELECT count(*),  FROM `laboratory_examinations` le
WHERE le.LaboratoryID = @VAR_LAB
    AND le.Date BETWEEN DATE( @DATE_BEGIN ) AND DATE( @DATE_END )
    AND le.FacilityID in (
        SELECT ID FROM `facilities`
        WHERE (
            ID = IFNULL(@VAR_FACILITY,ID) OR ParentID = IFNULL(@VAR_FACILITY,ParentID)
        )
    );