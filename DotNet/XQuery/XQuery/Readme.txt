数据表结构

USE [XQueryTest]
GO

/****** Object:  Table [dbo].[XQueryData]    Script Date: 10/21/2009 09:06:57 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[XQueryData](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[XmlData] [xml] NULL,
 CONSTRAINT [PK_XQueryData] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO




