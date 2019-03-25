-- phpMyAdmin SQL Dump
-- version 4.6.1
-- http://www.phpmyadmin.net
--
-- Host: mysql
-- Generation Time: Apr 05, 2018 at 10:55 AM
-- Server version: 5.7.21
-- PHP Version: 7.1.15

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `cursova`
--

DELIMITER $$
--
-- Procedures
--
DROP PROCEDURE IF EXISTS `sd_14_AverageExaminations`$$
CREATE DEFINER=`root`@`%` PROCEDURE `sd_14_AverageExaminations` (`VAR_LABORATORY` INT, `VAR_FACILITY` INT, `VAR_DATE_START` DATE, `VAR_DATE_END` DATE)  exit_point:BEGIN

        IF DATE(VAR_DATE_END) <= DATE(VAR_DATE_START) THEN
            SELECT "EXPECTING WIDER PERIOD; ABORT THIS MISSION";
            LEAVE exit_point;
        END IF; 


        SELECT count(*) / TIMESTAMPDIFF(DAY, VAR_DATE_START, VAR_DATE_END) as AVG_EXAMINATIONS_PER_DAY
        FROM `laboratory_examinations` le
        WHERE le.LaboratoryID = VAR_LABORATORY
        AND le.Date BETWEEN DATE( VAR_DATE_START ) AND DATE( VAR_DATE_END )
        AND le.FacilityID in (
            SELECT ID FROM `facilities`
            WHERE ( ID = IFNULL( VAR_FACILITY, ID ) 
                OR ParentID = IFNULL( VAR_FACILITY, ParentID ) )
        );

    END$$

DROP PROCEDURE IF EXISTS `sp_01_DoctorsBySpeciality`$$
CREATE DEFINER=`root`@`%` PROCEDURE `sp_01_DoctorsBySpeciality` (IN `VAR_SEARCH` VARCHAR(255), IN `VAR_FACULITY` INT, OUT `VAR_RECORDS` INT)  exit_point:BEGIN

                IF VAR_FACULITY <= 0 THEN 
            SELECT NULL INTO VAR_FACULITY; 
        END IF;
        
                CREATE TEMPORARY TABLE `temporary_DoctorsBySpeciality`  (
            ID INT(11)
        ) ENGINE=MEMORY; 
        
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

                SELECT COUNT(*) FROM `temporary_DoctorsBySpeciality` INTO VAR_RECORDS;
        
                IF VAR_RECORDS > 0 THEN
            SELECT `Name` FROM `workers` w WHERE w.ID IN (
                SELECT tmp.ID FROM `temporary_DoctorsBySpeciality` tmp
            );  
        END IF;

                DROP TABLE `temporary_DoctorsBySpeciality`;
    END$$

DROP PROCEDURE IF EXISTS `sp_02_StaffBySpeciality`$$
CREATE DEFINER=`root`@`%` PROCEDURE `sp_02_StaffBySpeciality` (IN `VAR_SEARCH` VARCHAR(255), IN `VAR_FACULITY` INT, OUT `VAR_RECORDS` INT)  exit_point:BEGIN

                IF VAR_FACULITY <= 0 THEN 
            SELECT NULL INTO VAR_FACULITY; 
        END IF;
        
                CREATE TEMPORARY TABLE `temporary_StaffBySpeciality`  (
            ID INT(11)
        ) ENGINE=MEMORY; 
        
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

                SELECT COUNT(*) FROM `temporary_StaffBySpeciality` INTO VAR_RECORDS;
        
                IF VAR_RECORDS > 0 THEN
            SELECT `Name` FROM `workers` w WHERE w.ID IN (
                SELECT tmp.ID FROM `temporary_StaffBySpeciality` tmp
            );  
        END IF;

                DROP TABLE `temporary_StaffBySpeciality`;
    END$$

DROP PROCEDURE IF EXISTS `sp_03_OperationsPerformedBy`$$
CREATE DEFINER=`root`@`%` PROCEDURE `sp_03_OperationsPerformedBy` (IN `VAR_SEARCH` VARCHAR(255), IN `VAR_LIMIT` INT, IN `VAR_FACILITY` INT, OUT `VAR_RECORDS` INT)  exit_point:BEGIN

                IF VAR_LIMIT < 0 THEN 
            SELECT "EXPECTING LIMIT => 0; ABORT THIS MISSION";
            SELECT 0 INTO VAR_RECORDS;
            LEAVE exit_point;
        END IF;

                IF VAR_FACILITY <= 0 THEN 
            SELECT NULL INTO VAR_FACILITY; 
        END IF;
        
                CREATE TEMPORARY TABLE `temporary_OperationsPerformedBy`  (
            ID INT(11)
        ) ENGINE=MEMORY; 
        
                INSERT INTO `temporary_OperationsPerformedBy` SELECT sd.WorkerID
        FROM `surgeries` s, `surgeries_doctors` sd
        WHERE s.FacilityID IN (
            SELECT ID FROM `facilities`
            WHERE ID = IFNULL(VAR_FACILITY, ID) 
                OR ParentID = IFNULL(VAR_FACILITY, ParentID)
        ) AND sd.WorkerID IN (
            SELECT WorkerID FROM `workers_specialities` ws 
            WHERE  sd.WorkerID = ws.WorkerID AND ws.SpecialityID IN (
                SELECT s.ID FROM `speciality` s 
                WHERE LOWER(s.Speciality) LIKE CONCAT('%', VAR_SEARCH, '%')
                    AND s.Type = 'Medical' 
            )
        ) AND s.ID = sd.SurgeryID 
        GROUP BY sd.WorkerID HAVING count(*) > VAR_LIMIT;

                SELECT COUNT(*) FROM `temporary_OperationsPerformedBy` INTO VAR_RECORDS;
        
                IF VAR_RECORDS > 0 THEN
            SELECT `Name` FROM workers w WHERE w.ID IN (
                SELECT tmp.ID FROM `temporary_OperationsPerformedBy` tmp
            );  
        END IF;

                DROP TABLE `temporary_OperationsPerformedBy`;
    END$$

DROP PROCEDURE IF EXISTS `sp_04_DoctorsYears`$$
CREATE DEFINER=`root`@`%` PROCEDURE `sp_04_DoctorsYears` (IN `VAR_SEARCH` VARCHAR(255), IN `VAR_YEARS` INT, IN `VAR_FACILITY` INT, OUT `VAR_RECORDS` INT)  exit_point:BEGIN

                IF VAR_YEARS < 0 THEN 
            SELECT "EXPECTING TOTAL_YEARS > 0; ABORT THIS MISSION";
            SELECT 0 INTO VAR_RECORDS;
            LEAVE exit_point;
        END IF;

                IF VAR_FACILITY <= 0 THEN 
            SELECT NULL INTO VAR_FACILITY; 
        END IF;
        
                CREATE TEMPORARY TABLE `temporary_DoctorsYears`  (
            ID    INT(11),
            Years INT (2)
        ) ENGINE=MEMORY; 
        
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

                SELECT COUNT(*) FROM `temporary_DoctorsYears` INTO VAR_RECORDS;
        
                IF VAR_RECORDS > 0 THEN
            SELECT `Name` FROM `workers` w WHERE w.ID IN (
                SELECT tmp.ID FROM `temporary_DoctorsYears` tmp
            );  
        END IF;

                DROP TABLE `temporary_DoctorsYears`;
    END$$

DROP PROCEDURE IF EXISTS `sp_05_AcademicTitle`$$
CREATE DEFINER=`root`@`%` PROCEDURE `sp_05_AcademicTitle` (IN `VAR_SEARCH` VARCHAR(255), IN `VAR_FACILITY` INT, OUT `VAR_RECORDS` INT)  exit_point:BEGIN

                IF VAR_FACILITY <= 0 THEN 
            SELECT NULL INTO VAR_FACILITY; 
        END IF;
        
                CREATE TEMPORARY TABLE `temporary_AcademicTitle`  (
            ID INT(11)
        ) ENGINE=MEMORY; 
        
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

                SELECT COUNT(*) FROM `temporary_AcademicTitle` INTO VAR_RECORDS;
        
                IF VAR_RECORDS > 0 THEN
            SELECT `Name` FROM `workers` w WHERE w.ID IN (
                SELECT tmp.ID FROM `temporary_AcademicTitle` tmp
            );  
        END IF;

                DROP TABLE `temporary_AcademicTitle`;

    END$$

DROP PROCEDURE IF EXISTS `sp_06_ongoingPatients`$$
CREATE DEFINER=`root`@`%` PROCEDURE `sp_06_ongoingPatients` (IN `VAR_FACILITY` INT, IN `VAR_DEPARTMENT` INT, IN `VAR_ROOM` INT)  exit_point:BEGIN
        DECLARE VALID_VARS INT DEFAULT 0;  

                IF VAR_FACILITY <= 0 THEN 
            SELECT NULL INTO VAR_FACILITY; 
        END IF;

        IF VAR_DEPARTMENT <= 0 THEN 
            SELECT NULL INTO VAR_DEPARTMENT; 
        END IF;
        
        IF VAR_ROOM <= 0 THEN 
            SELECT NULL INTO VAR_ROOM; 
        END IF;

    
                IF (VAR_FACILITY > 0) OR (VAR_ROOM > 0) OR  (VAR_DEPARTMENT > 0) THEN 
            SELECT 1 INTO VALID_VARS;
        END IF;

        IF VALID_VARS = 0 THEN 
            SELECT "EXPECTING AT LEAST NONE PARAM TO BE PROVIDED; ABORT THIS MISSION";
            LEAVE exit_point;
        END IF;
        

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
    END$$

DROP PROCEDURE IF EXISTS `sp_07_StationaryPatients`$$
CREATE DEFINER=`root`@`%` PROCEDURE `sp_07_StationaryPatients` (IN `VAR_FACILITY` INT, IN `VAR_DOCTOR` INT, IN `VAR_DATE_START` DATE, IN `VAR_DATE_END` DATE)  exit_point:BEGIN
        DECLARE RESULTS INT DEFAULT 0; 

                IF VAR_FACILITY < 0 THEN 
            SELECT NULL INTO VAR_FACILITY; 
        END IF;

        IF VAR_DOCTOR <= 0 THEN 
            SELECT NULL INTO VAR_DOCTOR; 
        END IF;

                if (VAR_FACILITY IS NULL AND VAR_DOCTOR IS NULL) OR 
           (VAR_FACILITY IS NOT NULL AND VAR_DOCTOR IS NOT NULL) THEN 
            SELECT "EXPECTING FACILITY OR DOCTOR, NOT BOTH, NOT NONE; ABORT THIS MISSION";
            LEAVE exit_point;
        END IF;

        IF DATE(VAR_DATE_END) <= DATE(VAR_DATE_START) THEN
            SELECT "EXPECTING WIDER PERIOD; ABORT THIS MISSION";
            LEAVE exit_point;
        END IF; 
      

                CREATE TEMPORARY TABLE `temporary__StationaryPatients`  (
            ID INT(11)
        ) ENGINE=MEMORY; 
        
                INSERT INTO `temporary__StationaryPatients` 
        SELECT r.PatientID FROM registry r
        WHERE  r.Type = 'Stationary'
        AND ( r.SignIn >= VAR_DATE_START AND r.SignOut <= VAR_DATE_END )
        AND ( FacilityID = IFNULL(VAR_FACILITY, -1)
        OR  DoctorID = IFNULL(VAR_DOCTOR, -1) );

                SELECT COUNT(*) FROM `temporary__StationaryPatients` INTO RESULTS;
        
                IF RESULTS > 0 THEN
            SELECT `Name` FROM `patients` p WHERE p.ID IN (
                SELECT tmp.ID FROM `temporary__StationaryPatients` tmp
            ); 
        END IF;

                DROP TABLE `temporary__StationaryPatients`;
    END$$

DROP PROCEDURE IF EXISTS `sp_08_SearchInHospitalBySpeciality`$$
CREATE DEFINER=`root`@`%` PROCEDURE `sp_08_SearchInHospitalBySpeciality` (IN `VAR_FACILITY` INT, IN `VAR_SEARCH` VARCHAR(255))  exit_point:BEGIN
        DECLARE RESULTS INT DEFAULT 0; 

                IF VAR_FACILITY <= 0 THEN 
            SELECT "EXPECTING FACILITY TO BE PROVIDED > ; ABORT THIS MISSION";
            LEAVE exit_point;
        END IF;

                IF VAR_FACILITY <= 0 THEN 
            SELECT NULL INTO VAR_FACILITY; 
        END IF;
        
                CREATE TEMPORARY TABLE `temporary__SearchInHospitalBySpeciality`  (
            ID INT(11)
        ) ENGINE=MEMORY; 
        
                INSERT INTO `temporary__SearchInHospitalBySpeciality` 
        SELECT r.PatientID  FROM registry r 
        WHERE r.DoctorID IN (
            SELECT f.WorkerID FROM workers_facilities f 
            WHERE f.FacilityID = VAR_FACILITY
            AND f.WorkerID in (
                SELECT ws.WorkerID FROM `workers_specialities` ws 
                WHERE  ws.SpecialityID IN (
                    SELECT s.ID FROM `speciality` s 
                    WHERE LOWER(s.Speciality) LIKE CONCAT('%', VAR_SEARCH, '%')
                    AND s.Type = 'Medical' 
                )
            )
            AND f.Status = 'Active'
        ) 
        AND r.FacilityID = VAR_FACILITY
        AND r.Type IN ('Ambulatory','Stationary','Periodic');

                SELECT COUNT(*) FROM `temporary__SearchInHospitalBySpeciality` INTO RESULTS;
        
                IF RESULTS > 0 THEN
             SELECT `Name` FROM `patients` p WHERE p.ID IN (
                SELECT tmp.ID FROM `temporary__SearchInHospitalBySpeciality` tmp
            );  
        END IF;

                DROP TABLE `temporary__SearchInHospitalBySpeciality`;
    END$$

DROP PROCEDURE IF EXISTS `sp_09_BedsAndRooms`$$
CREATE DEFINER=`root`@`%` PROCEDURE `sp_09_BedsAndRooms` (IN `VAR_FACILITY` INT)  exit_point:BEGIN

                IF VAR_FACILITY <= 0 THEN 
            SELECT "EXPECTING FACILITY TO BE PROVIDED; ABORT THIS MISSION";
            LEAVE exit_point;
        END IF;
     
        
                SELECT 
            IF( LOCATE(",", GROUP_CONCAT(t.Department)) = 0,  
			GROUP_CONCAT(t.Department), "Summary" ) as Department,
            SUM(t.Rooms) as Total_Rooms, 
            SUM(t.Beds) as Total_Beds, 
            SUM(t.Vacant_Rooms) as Vacant_Rooms, 
            SUM(t.Vacant_Rooms) as Vacant_Beds
        FROM (
            SELECT  
                dep.DepartmentID, 
                dep.Department, 
                dep.Rooms, 
                dep.Beds, 
                (dep.Rooms - IFNULL(busy.BusyRooms, 0)) as Vacant_Rooms, 
                (dep.Beds - IFNULL(busy.BusyBeds, 0)) as Vacant_Beds
            FROM (
                SELECT 
                    d.ID   as DepartmentID,
                    d.Name as Department, 
                    count(DISTINCT r.ID) as Rooms, 
                    count(b.ID) as Beds
                FROM 
                    `facilities_departments` d, 
                    `facilities_rooms` r, 
                    `facilities_rooms_beds` b 
                WHERE d.FacilityID = VAR_FACILITY
                    AND d.ID = r.DepartmentID 
                    AND r.ID = b.RoomID
                GROUP BY d.ID  
            ) dep
        LEFT JOIN (
            SELECT r.DepartmentID , 
                    count(DISTINCT r.RoomID) as BusyRooms,  
                    count(DISTINCT r.BedID) as BusyBeds
            FROM `registry` r
            WHERE r.FacilityID = VAR_FACILITY
            AND r.Type in ('Ambulatory', 'Stationary')
            AND ( r.SignOut IS NULL OR r.SignOut > NOW())
            AND r.SignIn < NOW() 
            GROUP BY r.DepartmentID
        )  busy  ON (  busy.DepartmentID = dep.DepartmentID ) ) t 
        GROUP BY t.DepartmentID
        WITH ROLLUP;
    END$$

DROP PROCEDURE IF EXISTS `sp_10_Cabinets`$$
CREATE DEFINER=`root`@`%` PROCEDURE `sp_10_Cabinets` (IN `VAR_DATE_START` DATE, IN `VAR_DATE_END` DATE, IN `VAR_FACILITY` INT, OUT `VAR_RECORDS` INT)  exit_point:BEGIN

                IF VAR_FACILITY < 0 THEN 
            SELECT "EXPECTING LIMIT => 0; ABORT THIS MISSION"; 
            LEAVE exit_point;
        END IF;

        IF DATE(VAR_DATE_END) <= DATE(VAR_DATE_START) THEN
            SELECT "EXPECTING WIDER PERIOD; ABORT THIS MISSION";
            LEAVE exit_point;
        END IF; 

            

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

                SELECT IFNULL(FOUND_ROWS(), 0) INTO VAR_RECORDS;

    END$$

DROP PROCEDURE IF EXISTS `sp_11_AvergagePatients`$$
CREATE DEFINER=`root`@`%` PROCEDURE `sp_11_AvergagePatients` (IN `VAR_DATE_START` DATE, IN `VAR_DATE_END` DATE, IN `VAR_DOCTOR` INT, IN `VAR_FACILITY` INT, IN `VAR_SEARCH` VARCHAR(255))  exit_point:BEGIN
        DECLARE RESULTS INT DEFAULT 0; 
        DECLARE SEARCH_EMPTY INT DEFAULT 0; 

                 IF DATE(VAR_DATE_END) <= DATE(VAR_DATE_START) THEN
            SELECT "EXPECTING WIDER PERIOD; ABORT THIS MISSION";
            LEAVE exit_point;
        END IF; 

                IF VAR_DOCTOR <= 0 THEN 
            SELECT NULL INTO VAR_DOCTOR; 
        END IF;
 
        IF VAR_FACILITY <= 0 THEN 
            SELECT NULL INTO VAR_FACILITY; 
        END IF;

        SELECT VAR_SEARCH = "" INTO SEARCH_EMPTY;

                 CREATE TEMPORARY TABLE IF NOT EXISTS `temporary__AvergagePatients`  (
            ID INT(11)
        ) ENGINE=MEMORY; 


                 IF VAR_DOCTOR > 0 THEN
            
            INSERT INTO `temporary__AvergagePatients` VALUES (VAR_DOCTOR);
        
        ELSEIF VAR_FACILITY > 0 THEN

            INSERT INTO `temporary__AvergagePatients` 
            SELECT DoctorID FROM registry 
            WHERE FacilityID = VAR_FACILITY GROUP BY DoctorID;

        ELSEIF SEARCH_EMPTY = 0 THEN

            INSERT INTO `temporary__AvergagePatients`
            SELECT wf.WorkerID FROM `workers_facilities` wf
            JOIN workers_specialities ws ON ( 
                wf.WorkerID = ws.WorkerID AND ws.SpecialityID IN (
                    SELECT s.ID FROM `speciality` s 
                    WHERE LOWER(s.Speciality) LIKE CONCAT('%', VAR_SEARCH,'%') 
                    AND s.Type = 'Medical' 
                )
            ) AND wf.Status = 'Active';

        ELSE
        
            SELECT "NO VALID INPUT VARS PROVIDED; ABORT THIS MISSION";
            LEAVE exit_point;

        END IF;

                SELECT COUNT(*) FROM `temporary__AvergagePatients` INTO RESULTS;
        
                IF RESULTS > 0 THEN

            SELECT AVG(r.PerDay) as Average_Patients_Per_Day FROM (
                SELECT DoctorID, SignIn, count(*) as PerDay FROM registry r
                WHERE r.Type IN ( 'Periodic', 'Regular' ) 
                AND r.SignIn BETWEEN VAR_DATE_START AND  VAR_DATE_END
                AND r.DoctorID IN (
                    SELECT tmp.ID FROM `temporary__AvergagePatients` tmp
                )
                GROUP BY r.DoctorID ASC, r.SignIn DESC
            ) as r;
        END IF; 
    END$$

DROP PROCEDURE IF EXISTS `sp_12_FamilyDoctor`$$
CREATE DEFINER=`root`@`%` PROCEDURE `sp_12_FamilyDoctor` (IN `VAR_DOCTOR` INT, IN `VAR_FACILITY` INT, IN `VAR_SEARCH` VARCHAR(255))  exit_point:BEGIN
        DECLARE RESULTS INT DEFAULT 0; 
        DECLARE SEARCH_EMPTY INT DEFAULT 0; 

                IF VAR_DOCTOR <= 0 THEN 
            SELECT NULL INTO VAR_DOCTOR; 
        END IF;
 
        IF VAR_FACILITY <= 0 THEN 
            SELECT NULL INTO VAR_FACILITY; 
        END IF;

        SELECT VAR_SEARCH = "" INTO SEARCH_EMPTY;

                 CREATE TEMPORARY TABLE IF NOT EXISTS `temporary__FamilyDoctor`  (
            ID INT(11)
        ) ENGINE=MEMORY; 


                 IF VAR_DOCTOR > 0 THEN
            
            INSERT INTO `temporary__FamilyDoctor` VALUES (VAR_DOCTOR);
        
        ELSEIF VAR_FACILITY > 0 THEN

            INSERT INTO `temporary__FamilyDoctor` 
            SELECT DoctorID FROM registry 
            WHERE FacilityID = VAR_FACILITY GROUP BY DoctorID;

        ELSEIF SEARCH_EMPTY = 0 THEN

            INSERT INTO `temporary__FamilyDoctor`
            SELECT wf.WorkerID FROM `workers_facilities` wf
            JOIN workers_specialities ws ON ( 
                wf.WorkerID = ws.WorkerID AND ws.SpecialityID IN (
                    SELECT s.ID FROM `speciality` s 
                    WHERE LOWER(s.Speciality) LIKE CONCAT('%', VAR_SEARCH,'%') 
                    AND s.Type = 'Medical' 
                )
            ) AND wf.Status = 'Active';

        ELSE
        
            SELECT "NO VALID INPUT VARS PROVIDED; ABORT THIS MISSION";
            LEAVE exit_point;

        END IF;

                SELECT COUNT(*) FROM `temporary__FamilyDoctor` INTO RESULTS;
        
                IF RESULTS > 0 THEN
            SELECT count(PerDay) FROM (
                SELECT DoctorID, SignIn, count(*) as PerDay FROM registry r
                WHERE r.Type IN ( 'Periodic', 'Ambulatory', 'Stationary' ) 
                AND r.SignIn > DATE_SUB(NOW(), INTERVAL 2 WEEK)
                AND r.DoctorID IN (
                    SELECT tmp.ID FROM `temporary__FamilyDoctor` tmp
                )
                GROUP BY r.DoctorID ASC, r.SignIn DESC
            ) as r;
        END IF; 
    END$$

DROP PROCEDURE IF EXISTS `sp_13_SurgeryPatients`$$
CREATE DEFINER=`root`@`%` PROCEDURE `sp_13_SurgeryPatients` (IN `DATE_BEGIN` DATE, IN `DATE_END` DATE, IN `VAR_DOCTOR` INT, IN `VAR_FACILITY` INT, OUT `VAR_RECORDS` INT)  exit_point:BEGIN

                IF VAR_FACILITY > 0 AND VAR_DOCTOR > 0 THEN 
            SELECT "EXPECTING FACILITY OR DOCTOR <= 0; ABORT THIS MISSION";
            SELECT 0 INTO VAR_RECORDS;
            LEAVE exit_point;
        END IF;

               IF VAR_FACILITY <= 0 THEN 
            SELECT NULL INTO VAR_FACILITY; 
        END IF;

        IF VAR_DOCTOR <= 0 THEN 
            SELECT NULL INTO VAR_DOCTOR; 
        END IF;
        
                IF VAR_FACILITY IS NULL AND VAR_DOCTOR IS NULL THEN 
            SELECT "EXPECTING FACILITY OR DOCTOR > 0; ABORT THIS MISSION";
            SELECT 0 INTO VAR_RECORDS;
            LEAVE exit_point;
        END IF;

        IF DATE(DATE_END) <= DATE(DATE_BEGIN) THEN
            SELECT "EXPECTING WIDER PERIOD; ABORT THIS MISSION";
            SELECT 0 INTO VAR_RECORDS;
            LEAVE exit_point;
        END IF; 
        
                CREATE TEMPORARY TABLE `temporary_SurgeryPatients`  (
            ID INT(11)
        ) ENGINE=MEMORY; 
        
                INSERT INTO `temporary_SurgeryPatients` 
        SELECT p.ID FROM `patients` p 
        WHERE p.ID IN (
            SELECT s.PatientID FROM `surgeries` s, `surgeries_doctors` sd
            WHERE s.ID = sd.SurgeryID 
            AND DATE(s.Date) BETWEEN DATE( DATE_BEGIN ) AND DATE( DATE_END )
            AND ( sd.WorkerID = VAR_DOCTOR OR s.FacilityID IN (
                    SELECT ID FROM `facilities`
                    WHERE ( ID = VAR_FACILITY OR ParentID = VAR_FACILITY )
                ) 
            )   
        );

                                                                                        
                SELECT COUNT(*) FROM `temporary_SurgeryPatients` INTO VAR_RECORDS;
        
                IF VAR_RECORDS > 0 THEN
            SELECT `Name` FROM `patients` p WHERE p.ID IN (
                SELECT tmp.ID FROM `temporary_SurgeryPatients` tmp
            );  
        END IF;

                DROP TABLE `temporary_SurgeryPatients`;
    END$$

DROP PROCEDURE IF EXISTS `sp_demo`$$
CREATE DEFINER=`root`@`%` PROCEDURE `sp_demo` (OUT `VAR_RECORDS` INT)  BEGIN
    CREATE TABLE t (qty INT, price INT);
    INSERT INTO t VALUES(3, 50);
    CREATE VIEW v AS SELECT qty, price, qty*price AS value FROM t ;
    SELECT count(*) FROM v WHERE qty > 3 AND 1=2;
    DROP VIEW v;
    DROP TABLE t;
END$$

DELIMITER ;

-- --------------------------------------------------------

--
-- Table structure for table `facilities`
--

DROP TABLE IF EXISTS `facilities`;
CREATE TABLE `facilities` (
  `ID` int(11) NOT NULL,
  `ParentID` int(11) DEFAULT NULL,
  `Type` enum('Hospital','Laboratory','Clinic') DEFAULT NULL,
  `Title` varchar(255) NOT NULL,
  `Affiliation` enum('Goverment','Dobrobut','Sinevo') NOT NULL,
  `Address` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `facilities_departments`
--

DROP TABLE IF EXISTS `facilities_departments`;
CREATE TABLE `facilities_departments` (
  `ID` int(11) NOT NULL,
  `FacilityID` int(11) NOT NULL,
  `Name` varchar(32) NOT NULL COMMENT 'Назва відділеня'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `facilities_rooms`
--

DROP TABLE IF EXISTS `facilities_rooms`;
CREATE TABLE `facilities_rooms` (
  `ID` int(11) NOT NULL,
  `FacilityID` int(11) NOT NULL,
  `DepartmentID` int(11) DEFAULT '-1',
  `Type` enum('Cabinet','Ambulatory','Procedural') NOT NULL,
  `Number` varchar(6) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `facilities_rooms_beds`
--

DROP TABLE IF EXISTS `facilities_rooms_beds`;
CREATE TABLE `facilities_rooms_beds` (
  `ID` int(11) NOT NULL,
  `FacilityID` int(4) NOT NULL,
  `RoomID` int(4) NOT NULL,
  `Type` enum('Regular','Standard','Luxury') DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `laboratories`
--

DROP TABLE IF EXISTS `laboratories`;
CREATE TABLE `laboratories` (
  `LaboratoryID` int(11) NOT NULL COMMENT 'ID Лабораторії (співпадає з FacilityID)',
  `ExaminationTypeInclude` int(11) DEFAULT NULL COMMENT 'Включенни тестів',
  `ExaminationTypeExclude` int(11) DEFAULT NULL COMMENT 'Виключення тестів'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `laboratory_contracts`
--

DROP TABLE IF EXISTS `laboratory_contracts`;
CREATE TABLE `laboratory_contracts` (
  `ID` int(11) NOT NULL,
  `LaboratoryID` int(11) NOT NULL,
  `FacilityID` int(11) NOT NULL,
  `Start` date NOT NULL,
  `End` date DEFAULT NULL,
  `Type` enum('Active','None') NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `laboratory_examinations`
--

DROP TABLE IF EXISTS `laboratory_examinations`;
CREATE TABLE `laboratory_examinations` (
  `ID` int(11) NOT NULL,
  `LaboratoryID` int(11) NOT NULL,
  `FacilityID` int(11) NOT NULL,
  `PatientID` int(11) NOT NULL,
  `Date` date NOT NULL,
  `ExaminationID` int(11) NOT NULL,
  `Conclusion` text
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `laboratory_examination_types`
--

DROP TABLE IF EXISTS `laboratory_examination_types`;
CREATE TABLE `laboratory_examination_types` (
  `ID` int(11) NOT NULL,
  `ParentID` int(11) DEFAULT NULL,
  `Type` enum('Category','Test') NOT NULL,
  `Code` varchar(32) DEFAULT NULL,
  `Title` varchar(255) NOT NULL,
  `Note` text
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `patients`
--

DROP TABLE IF EXISTS `patients`;
CREATE TABLE `patients` (
  `ID` int(11) NOT NULL,
  `Name` varchar(255) NOT NULL,
  `Gender` enum('Male','Female') NOT NULL,
  `Birth` date DEFAULT NULL,
  `Phone` varchar(24) DEFAULT NULL,
  `Adress` varchar(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `registry`
--

DROP TABLE IF EXISTS `registry`;
CREATE TABLE `registry` (
  `ID` int(11) NOT NULL,
  `Type` enum('Ambulatory','Stationary','Regular','Periodic') DEFAULT NULL,
  `FacilityID` int(11) NOT NULL,
  `DepartmentID` int(11) NOT NULL,
  `RoomID` int(11) NOT NULL,
  `BedID` int(11) NOT NULL DEFAULT '0',
  `DoctorID` int(11) NOT NULL,
  `PatientID` int(11) NOT NULL,
  `Temperature` float DEFAULT NULL,
  `Notes` text,
  `SignIn` date NOT NULL,
  `SignOut` date DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `speciality`
--

DROP TABLE IF EXISTS `speciality`;
CREATE TABLE `speciality` (
  `ID` int(11) NOT NULL,
  `Speciality` varchar(255) NOT NULL,
  `Type` enum('Medical','Technical','Administrative','Other') NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `surgeries`
--

DROP TABLE IF EXISTS `surgeries`;
CREATE TABLE `surgeries` (
  `ID` int(11) NOT NULL,
  `FacilityID` int(11) NOT NULL,
  `PatientID` int(11) NOT NULL,
  `Date` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='Таблиця основної операції по операціях';

-- --------------------------------------------------------

--
-- Table structure for table `surgeries_doctors`
--

DROP TABLE IF EXISTS `surgeries_doctors`;
CREATE TABLE `surgeries_doctors` (
  `ID` int(11) NOT NULL COMMENT 'ID in Table',
  `SurgeryID` int(11) NOT NULL,
  `WorkerID` int(11) NOT NULL,
  `Role` varchar(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `workers`
--

DROP TABLE IF EXISTS `workers`;
CREATE TABLE `workers` (
  `ID` int(11) NOT NULL,
  `Name` varchar(255) NOT NULL COMMENT 'Doctor''s Name',
  `_Type` enum('Medical','Technical','Administrative','Other') NOT NULL,
  `_Position` varchar(255) DEFAULT NULL COMMENT 'Посада',
  `_Since` date DEFAULT NULL COMMENT 'Working Since [date]',
  `_Description` text COMMENT 'Інформація'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `workers_facilities`
--

DROP TABLE IF EXISTS `workers_facilities`;
CREATE TABLE `workers_facilities` (
  `ID` int(11) NOT NULL,
  `FacilityID` int(11) NOT NULL,
  `WorkerID` int(11) NOT NULL,
  `Start` date DEFAULT NULL,
  `End` date DEFAULT NULL,
  `Role` varchar(255) DEFAULT NULL,
  `Type` enum('Medical','Technical','Administrative','Other') NOT NULL,
  `Status` enum('Active','None') NOT NULL,
  `Notes` text
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='Описує відношення мід лікарами та медичними закладами';

-- --------------------------------------------------------

--
-- Table structure for table `workers_specialities`
--

DROP TABLE IF EXISTS `workers_specialities`;
CREATE TABLE `workers_specialities` (
  `ID` int(11) NOT NULL,
  `WorkerID` int(11) NOT NULL,
  `SpecialityID` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `workers_titles`
--

DROP TABLE IF EXISTS `workers_titles`;
CREATE TABLE `workers_titles` (
  `ID` int(11) NOT NULL,
  `WorkerID` int(11) NOT NULL,
  `Type` enum('Academic','Profesional','Membership') NOT NULL,
  `Title` varchar(255) NOT NULL,
  `Details` text,
  `Date` date DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='Doctors Titles';

--
-- Indexes for dumped tables
--

--
-- Indexes for table `facilities`
--
ALTER TABLE `facilities`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `facilities_departments`
--
ALTER TABLE `facilities_departments`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `FacilityID` (`FacilityID`);

--
-- Indexes for table `facilities_rooms`
--
ALTER TABLE `facilities_rooms`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `DepartmentID` (`DepartmentID`);

--
-- Indexes for table `facilities_rooms_beds`
--
ALTER TABLE `facilities_rooms_beds`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `RoomID` (`RoomID`);

--
-- Indexes for table `laboratory_contracts`
--
ALTER TABLE `laboratory_contracts`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `laboratory_examinations`
--
ALTER TABLE `laboratory_examinations`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `FacilityID` (`FacilityID`);

--
-- Indexes for table `laboratory_examination_types`
--
ALTER TABLE `laboratory_examination_types`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `ParentID` (`ParentID`);

--
-- Indexes for table `patients`
--
ALTER TABLE `patients`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `registry`
--
ALTER TABLE `registry`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `FacilityID` (`FacilityID`,`SignIn`,`SignOut`),
  ADD KEY `RoomID` (`RoomID`);

--
-- Indexes for table `speciality`
--
ALTER TABLE `speciality`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `surgeries`
--
ALTER TABLE `surgeries`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `FacilityID` (`FacilityID`),
  ADD KEY `PatientID` (`PatientID`);

--
-- Indexes for table `surgeries_doctors`
--
ALTER TABLE `surgeries_doctors`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `SurgeryID` (`SurgeryID`);

--
-- Indexes for table `workers`
--
ALTER TABLE `workers`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `workers_facilities`
--
ALTER TABLE `workers_facilities`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `FacilityID` (`FacilityID`,`WorkerID`);

--
-- Indexes for table `workers_specialities`
--
ALTER TABLE `workers_specialities`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `WorkerID` (`WorkerID`,`SpecialityID`);

--
-- Indexes for table `workers_titles`
--
ALTER TABLE `workers_titles`
  ADD PRIMARY KEY (`ID`),
  ADD KEY `WorkerID` (`WorkerID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `facilities`
--
ALTER TABLE `facilities`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=59;
--
-- AUTO_INCREMENT for table `facilities_departments`
--
ALTER TABLE `facilities_departments`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=34;
--
-- AUTO_INCREMENT for table `facilities_rooms`
--
ALTER TABLE `facilities_rooms`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=853;
--
-- AUTO_INCREMENT for table `facilities_rooms_beds`
--
ALTER TABLE `facilities_rooms_beds`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1026;
--
-- AUTO_INCREMENT for table `laboratory_contracts`
--
ALTER TABLE `laboratory_contracts`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=17;
--
-- AUTO_INCREMENT for table `laboratory_examinations`
--
ALTER TABLE `laboratory_examinations`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=15697;
--
-- AUTO_INCREMENT for table `laboratory_examination_types`
--
ALTER TABLE `laboratory_examination_types`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=717;
--
-- AUTO_INCREMENT for table `patients`
--
ALTER TABLE `patients`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12047;
--
-- AUTO_INCREMENT for table `registry`
--
ALTER TABLE `registry`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=80514;
--
-- AUTO_INCREMENT for table `speciality`
--
ALTER TABLE `speciality`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=68;
--
-- AUTO_INCREMENT for table `surgeries`
--
ALTER TABLE `surgeries`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=919;
--
-- AUTO_INCREMENT for table `surgeries_doctors`
--
ALTER TABLE `surgeries_doctors`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT COMMENT 'ID in Table', AUTO_INCREMENT=919;
--
-- AUTO_INCREMENT for table `workers`
--
ALTER TABLE `workers`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=666;
--
-- AUTO_INCREMENT for table `workers_facilities`
--
ALTER TABLE `workers_facilities`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=751;
--
-- AUTO_INCREMENT for table `workers_specialities`
--
ALTER TABLE `workers_specialities`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=957;
--
-- AUTO_INCREMENT for table `workers_titles`
--
ALTER TABLE `workers_titles`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=554;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
