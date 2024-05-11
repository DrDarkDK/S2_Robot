CREATE DATABASE IF NOT EXISTS RobotDB;

Use RobotDB;

CREATE TABLE movement (
    move_id int not null AUTO_INCREMENT,
    posX double not null,
    posY double not null,
    posZ double not null,
    primary key(move_id)
);

/* Fix old code */
ALTER TABLE movement MODIFY COLUMN move_id int NOT NULL AUTO_INCREMENT;

ALTER TABLE movement MODIFY posX double NOT NULL;
ALTER TABLE movement MODIFY posY double NOT NULL;
ALTER TABLE movement MODIFY posZ double NOT NULL;

CREATE TABLE voltage (
    voltage_id int not null AUTO_INCREMENT,
    timestamp VARCHAR(255) not null,
    spaending double not null,
);
