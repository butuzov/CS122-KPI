
SelectDoctors
begin
SELECT @group := `group` FROM user WHERE user = @user;
    SELECT * FROM doctors LIMIT page; 
end



Sample Stoed Procedure

-- Simple testing of procedures
DELIMITER $$

DROP PROCEDURE IF EXISTS SP_Test $$

CREATE PROCEDURE SP_Test () 
    BEGIN
        SELECT NOW();
    END $$

DELIMITER ;

CALL SP_Test()

==================

-- Math testing of procedures

DELIMITER $$

DROP PROCEDURE IF EXISTS SP_Test $$

CREATE PROCEDURE SP_Test (IN rec_per_page INT, IN page_number INT) 
    BEGIN
        DECLARE start_from INT DEFAULT 0;
        SELECT (rec_per_page * page_number) - rec_per_page  INTO start_from;
        SELECT * FROM `doctors` LIMIT start_from, rec_per_page;
    END $$

DELIMITER ;

CALL SP_Test(10, 2)

==================


DELIMITER $$

DROP PROCEDURE IF EXISTS PrSelectDoctors $$

CREATE PROCEDURE PrSelectDoctors(IN rec_per_page INT, IN page_number INT) 
    BEGIN
        DECLARE start_from INT DEFAULT 0;
        SELECT (rec_per_page * page_number) - rec_per_page  INTO start_from;
        SELECT * FROM `doctors` LIMIT start_from, rec_per_page;
    END $$

DELIMITER ;

CALL PrSelectDoctors(10, 1);
CALL PrSelectDoctors(10);

=================

-- Top n Doctors by number  

DELIMITER $$

DROP PROCEDURE IF EXISTS PrMostAvailableDoctos $$

CREATE PROCEDURE PrMostAvailableDoctos(IN topest INT) 
    BEGIN
        SELECT Position FROM `doctors` GROUP BY `Position` ORDER by COUNT(*) ASC LIMIT topest;
    END $$

DELIMITER ;

=================

-- Average Sallary (Query)

SELECT Position, ROUND( SUM(Sallary) / COUNT(*), 2) as AverageSallary FROM `doctors`  GROUP BY `Position`

================


-- Top Sallry

DELIMITER $$

DROP PROCEDURE IF EXISTS SpTopSallery $$

CREATE PROCEDURE SpTopSallery(OUT topsallary FLOAT) 
    BEGIN
        SELECT MAX(Sallary)INTO topsallary FROM `doctors`;
    END $$

DELIMITER ;
 

-- Selection of doctors that receive sallary with in 90% of max 
-- sallary paid to doctors in this hospital.
CALL SpTopSallery(@p);
SELECT * from doctors where Sallary > @p * 0.9;

================



DELIMITER $$

DROP PROCEDURE IF EXISTS SpSallary $$

CREATE PROCEDURE SpSallary (OUT total INT, IN iSallary FLOAT) 
BEGIN
    DECLARE limit_amount INT DEFAULT 15000;

    CASE
        WHEN (iSallary > limit_amount)
            THEN (
                SELECT COUNT(ID) INTO total FROM doctors 
                WHERE Sallary > limit_amount );
        WHEN (iSallary < limit_amount)
            THEN (
                SELECT COUNT(ID) INTO total FROM doctors 
                WHERE Sallary < limit_amount
            );
        ELSE (
            SELECT COUNT(ID) INTO total FROM doctors 
            WHERE Sallary = limit_amount
        );
    END CASE; 
END $$ 

DELIMITER ;


CALL SpSallary(@out1, 16000);
CALL SpSallary(@out2, 15000);
CALL SpSallary(@out3, 14000);
SELECT @out1 as "About 16k", @out2 as "Exactly 15k", @out3 as "Less then 15k";


------------

-- Functions 
DELIMITER $$

DROP FUNCTION IF EXISTS FnTotalDoctorsWithContracts$$

CREATE FUNCTION FnTotalDoctorsWithContracts() RETURNS INT 
BEGIN
    DECLARE n INT;
    SELECT count(*) INTO n FROM `doctors` d INNER JOIN `contracts` c ON ( c.DoctorID = d.ID );
    return n;
END $$ 
DELIMITER ;

SELECT FnTotalDoctorsWithContracts();


====

DELIMITER $$

DROP PROCEDURE IF EXISTS PrCreateContract$$

CREATE PROCEDURE PrCreateContract( IN DoctorId INT, IN SignUpDate DATE, IN StartDate DATE, IN EndDate DATE, IN Amount FLOAT) 
BEGIN
    DECLARE found INT default 0;
    SELECT count(*) into found  FROM `contracts` c, `doctors` d 
    WHERE d.ID = DoctorId  AND d.ID = c.DoctorID 
        AND c.Date_Signup = SignUpDate
        AND c.Date_Start = StartDate
        AND c.Date_End = EndDate
        AND c.Amount = Amount;

    IF (found=0) 
        THEN  BEGIN
            INSERT INTO `contracts` (`DoctorID`, `Date_Signup`, `Date_Start`, `Date_End`, `Amount`) VALUES ( DoctorId,  SignUpDate, StartDate, EndDate , Amount);

            SELECT "S:CONTRACT_CREATED"; 
        
        END;
    ELSE
        BEGIN
            SELECT "F:CONTRACT_EXISTS"; 
        END;
    END IF;
END $$ 

DELIMITER ;

-- Duplicate

CALL PrCreateContract( 1, NOW(), NOW(), NOW(), 1);
CALL PrCreateContract( 1, NOW(), NOW(), NOW(), 1);

CALL PrCreateContract( 19, '2018-01-02', '2018-02-01', DATE_SUB("2018-02-01", INTERVAL -1 YEAR), 10000);
CALL PrCreateContract( 35, '2018-01-02', '2018-03-01', DATE_SUB("2018-02-01", INTERVAL -1 YEAR), 17000);

======


samples 
SELECT LOWER(Name) FROM `doctors`
UPDATE `doctors` SET Position = LOWER(Position)




DELIMITER $$

DROP FUNCTION IF EXISTS FnCapitalize$$

CREATE FUNCTION FnCapitalize ( word CHAR(255) ) RETURNS CHAR(255) DETERMINISTIC
BEGIN
    RETURN CONCAT(UPPER(SUBSTR(word, 1, 1)), LOWER(SUBSTR(word,2)));
END $$ 


DROP PROCEDURE IF EXISTS PrRandomDoctors$$

CREATE PROCEDURE PrRandomDoctors(IN n INT) 
BEGIN
    SELECT Name, FnCapitalize(Position) FROM `doctors` ORDER BY RAND() LIMIT n;
END $$

DELIMITER ;

Call PrRandomDoctors(3);
 
 