 DELIMITER $$

DROP PROCEDURE IF EXISTS sp_09_BedsAndRooms $$

CREATE PROCEDURE sp_09_BedsAndRooms(  
    IN  VAR_FACILITY INT) 
exit_point:BEGIN

        -- Validating Requied Variables.
        IF VAR_FACILITY <= 0 THEN 
            SELECT "EXPECTING FACILITY TO BE PROVIDED; ABORT THIS MISSION";
            LEAVE exit_point;
        END IF;
     
        
        -- Performing Heavy Selection.
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
    END $$
DELIMITER ;

-- Examples 

CALL sp_09_BedsAndRooms(1);
CALL sp_09_BedsAndRooms(5);
CALL sp_09_BedsAndRooms(6);