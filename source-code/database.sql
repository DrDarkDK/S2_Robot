CREATE DATABASE IF NOT EXISTS RobotDB;

Use RobotDB;

CREATE TABLE movement (
    move_id int not null,
    posX int not null,
    posY int not null,
    posZ int not null,
    primary key(move_id)
);