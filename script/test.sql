CREATE TABLE NATION (
 N_NATIONKEY INTEGER NOT NULL,
 N_NAME CHAR(25) NOT NULL,
 N_REGIONKEY INTEGER NOT NULL,
 N_COMMENT VARCHAR(152)
);

CREATE TABLE REGION (
 R_REGIONKEY INTEGER NOT NULL,
 R_NAME CHAR(25) NOT NULL,
 R_COMMENT VARCHAR(152)
);



\copy NATION FROM 'data/nation.tbl' DELIMITER AS '|';
\copy REGION FROM 'data/region.tbl' DELIMITER AS '|';