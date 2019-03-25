DELIMITER $$

DROP PROCEDURE IF EXISTS sp_06_ongoingPatients $$

CREATE PROCEDURE sp_06_ongoingPatients( 
    IN  VAR_FACILITY   INT, 
    IN  VAR_DEPARTMENT INT, 
    IN  VAR_ROOM       INT) 
exit_point:BEGIN
        DECLARE VALID_VARS INT DEFAULT 0;  

        -- Optional Variables
        IF VAR_FACILITY <= 0 THEN 
            SELECT NULL INTO VAR_FACILITY; 
        END IF;

        IF VAR_DEPARTMENT <= 0 THEN 
            SELECT NULL INTO VAR_DEPARTMENT; 
        END IF;
        
        IF VAR_ROOM <= 0 THEN 
            SELECT NULL INTO VAR_ROOM; 
        END IF;

    
        -- Validating Requied Variables.
        IF (VAR_FACILITY > 0) OR (VAR_ROOM > 0) OR  (VAR_DEPARTMENT > 0) THEN 
            SELECT 1 INTO VALID_VARS;
        END IF;

        IF VALID_VARS = 0 THEN 
            SELECT "EXPECTING AT LEAST NONE PARAM TO BE PROVIDED; ABORT THIS MISSION";
            LEAVE exit_point;
        END IF;
        

        -- Actial Slelrct Variables.
        SELECT
            p.Name as Patient, 
            r.SignIn, CONCAT(r.Temperature, "°C") as BodyTemperatureOnSignIn, fd.ID as DepartmentID,
            fd.Name as Department, 
            fr.ID as RoomID, 
            fr.Number as Room,  
            w.Name as Doctor
        FROM `registry` r
        LEFT JOIN `patients` AS p ON ( p.ID = r.PatientID )
        LEFT JOIN `workers` AS w ON ( w.ID = r.DoctorID ) 
        LEFT JOIN `facilities_departments` AS fd ON ( fd.ID = r.DepartmentID ) 
        LEFT JOIN `facilities_rooms` AS fr ON ( fr.ID = r.RoomID ) 
        WHERE (
            ( r.SignOut IS NULL OR r.SignOut > NOW()) AND r.SignIn < NOW()
        )
            AND r.FacilityID   = IFNULL( VAR_FACILITY,   r.FacilityID )
            AND r.DepartmentID = IFNULL( VAR_DEPARTMENT, r.DepartmentID )
            AND r.RoomID       = IFNULL( VAR_ROOM,       r.RoomID )
        ORDER BY r.SignIn ASC;
    END $$
DELIMITER ;
  

  -- Just Hospital 1
-- CALL sp_06_ongoingPatients(1,null, null);

-- Just Hospital 1, Department 3
-- CALL sp_06_ongoingPatients(1, 3, null);

-- Just Hospital 1, Department 3, Room ID 299 
-- CALL sp_06_ongoingPatients(1, 3, 299);

-- Calling directlty room 299
-- CALL sp_06_ongoingPatients(null, null, 299);

-- Empty Call
CALL sp_06_ongoingPatients(null, null, null);