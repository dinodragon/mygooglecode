CREATE USER MSPETSHOP4 IDENTIFIED BY "pass@word1" DEFAULT TABLESPACE USERS QUOTA UNLIMITED ON USERS; 

GRANT CREATE SESSION TO MSPETSHOP4; 
    
CREATE TABLE MSPETSHOP4.SUPPLIER (
    SuppId int NOT NULL,
    Name varchar(80) NULL,
    Status varchar(2) NOT NULL,
    Addr1 varchar(80) NULL,
    Addr2 varchar(80) NULL,
    City varchar(80) NULL,
    State varchar(80) NULL,
    Zip varchar(5) NULL,
    Phone varchar(80) NULL,
    CONSTRAINT PK_SUPPLIER PRIMARY KEY (SuppId) );

CREATE TABLE MSPETSHOP4.CATEGORY (
    CategoryId  varchar(10) NOT NULL,
    Name varchar(80) NULL,
    Descn varchar(255) NULL,
    CONSTRAINT PK_CATEGORY PRIMARY KEY (CategoryId) );

CREATE TABLE MSPETSHOP4.PRODUCT (
    ProductId varchar(10) NOT NULL,
    CategoryId varchar(10) NOT NULL,
    Name varchar(80) NULL,
    Descn varchar(255) NULL,
    Image varchar(80) NULL,
    CONSTRAINT PK_PRODUCT PRIMARY KEY (ProductId),
        CONSTRAINT FK_PRODUCT FOREIGN KEY (CategoryId)
        REFERENCES MSPETSHOP4.CATEGORY (CategoryId) );
        
CREATE TABLE MSPETSHOP4.ITEM (
    ItemId varchar(10) NOT NULL,
    ProductId varchar(10) NOT NULL,
    ListPrice decimal(10,2) NULL,
    UnitCost decimal(10,2) NULL,
    Supplier int NULL,
    Status varchar(2) NULL,
    Name varchar(80) NULL,
    Image varchar(80) NULL,
    CONSTRAINT PK_ITEM PRIMARY KEY (ItemId),
        CONSTRAINT FK_ITEM_1 FOREIGN KEY (ProductId)
        REFERENCES MSPETSHOP4.PRODUCT (ProductId),
        CONSTRAINT FK_ITEM_2 FOREIGN KEY (Supplier)
        REFERENCES MSPETSHOP4.SUPPLIER (SuppId) );
        
CREATE TABLE MSPETSHOP4.INVENTORY (
    ItemId varchar(10) NOT NULL,
    Qty int NOT NULL,
    CONSTRAINT PK_INVENTORY PRIMARY KEY(ItemId) );
    
CREATE INDEX MSPETSHOP4.IX_ITEM 
    ON MSPETSHOP4.ITEM (ProductId, ItemId, ListPrice, NAME);

CREATE INDEX MSPETSHOP4.IX_PRODUCT1
    ON MSPETSHOP4.PRODUCT (NAME);

CREATE INDEX MSPETSHOP4.IX_PRODUCT2
    ON MSPETSHOP4.PRODUCT (CategoryId);

CREATE INDEX MSPETSHOP4.IX_PRODUCT3
    ON MSPETSHOP4.PRODUCT (CategoryId, Name);

CREATE INDEX MSPETSHOP4.IX_PRODUCT4
    ON MSPETSHOP4.PRODUCT (CategoryId, ProductId, Name);