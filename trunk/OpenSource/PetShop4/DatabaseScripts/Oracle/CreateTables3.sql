CREATE USER MSPETSHOP4PROFILE  PROFILE DEFAULT IDENTIFIED BY "pass@word1" DEFAULT TABLESPACE USERS QUOTA UNLIMITED ON USERS;
					       
GRANT CREATE SESSION TO MSPETSHOP4PROFILE; 
    
CREATE TABLE MSPETSHOP4PROFILE.PROFILES (
	UniqueId number NOT NULL, 
    UserName varchar2(256 byte) NOT NULL, 
    ApplicationName varchar2(256 byte) NOT NULL, 
    IsAnonymous char(1 byte) NOT NULL, 
    LastActivityDate date NOT NULL, 
    LastUpdatedDate date NOT NULL,
    CONSTRAINT PK_PROFILES_1 PRIMARY KEY(UniqueId) 
		USING INDEX);
    
CREATE TABLE MSPETSHOP4PROFILE.CART (
    UniqueId number NOT NULL, 
    ItemId varchar2(10 byte) NOT NULL, 
    Name varchar2(80 byte) NOT NULL, 
    Type varchar2(80 byte) NOT NULL, 
    Price number(10, 2) NOT NULL, 
    CategoryId varchar2(10 byte) NOT NULL, 
    ProductId varchar2(10 byte) NOT NULL, 
    IsShoppingCart char(1 byte) NOT NULL, 
    Quantity number(10) NOT NULL,     
    CONSTRAINT FK_CART_PROFILES FOREIGN KEY(UniqueId) 
		REFERENCES MSPETSHOP4PROFILE.PROFILES(UniqueId) 
		ON DELETE CASCADE);
    
CREATE TABLE MSPETSHOP4PROFILE.ACCOUNT (
    UniqueId number(10)NOT NULL, 
    Email varchar2(80 byte), 
    FirstName varchar2(80 byte), 
    LastName varchar2(80 byte), 
    Address1 varchar2(80 byte), 
    Address2 varchar2(80 byte), 
    City varchar2(80 byte),
    State varchar2(80 byte), 
    Zip varchar2(20 byte), 
    Country varchar2(20 byte), 
    Phone varchar2(20 byte), 
    CONSTRAINT FK_ACCOUNT_PROFILES FOREIGN KEY(UniqueId) 
		REFERENCES MSPETSHOP4PROFILE.PROFILES(UniqueId) 
		ON DELETE CASCADE);  
    
CREATE SEQUENCE MSPETSHOP4PROFILE.UNIQUEID INCREMENT BY 1 
    START WITH 1 MAXVALUE 1.0E27 MINVALUE 1 NOCYCLE 
    CACHE 10000 NOORDER;    

CREATE INDEX MSPETSHOP4PROFILE.FK_CART_UNIQUEID 
    ON MSPETSHOP4PROFILE.CART  (UniqueId);
    
CREATE INDEX MSPETSHOP4PROFILE.FK_ACCOUNT_UNIQUEID 
    ON MSPETSHOP4PROFILE.ACCOUNT  (UniqueId);
    
CREATE UNIQUE INDEX MSPETSHOP4PROFILE.IX_USERNAME_APPNAME 
    ON MSPETSHOP4PROFILE.PROFILES  (UserName, ApplicationName);
    
CREATE BITMAP INDEX MSPETSHOP4PROFILE.IX_SHOPPINGCART 
    ON MSPETSHOP4PROFILE.CART  (IsShoppingCart);