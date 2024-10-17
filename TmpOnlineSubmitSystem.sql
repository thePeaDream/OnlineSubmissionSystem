-- MySQL dump 10.13  Distrib 8.0.36, for Win64 (x86_64)
--
-- Host: localhost    Database: onlineSubmitSystem
-- ------------------------------------------------------
-- Server version	8.0.36

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `admin`
--

DROP TABLE IF EXISTS `admin`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `admin` (
  `adminId` int NOT NULL COMMENT '管理员id',
  PRIMARY KEY (`adminId`),
  CONSTRAINT `admin_ibfk_1` FOREIGN KEY (`adminId`) REFERENCES `user` (`userId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `admin`
--

LOCK TABLES `admin` WRITE;
/*!40000 ALTER TABLE `admin` DISABLE KEYS */;
/*!40000 ALTER TABLE `admin` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `assessor`
--

DROP TABLE IF EXISTS `assessor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `assessor` (
  `assessorId` int NOT NULL COMMENT '审核id',
  `pendingAudit` int DEFAULT NULL COMMENT '待审核的稿件数目',
  `completeAudit` int DEFAULT NULL COMMENT '已审核的稿件数目',
  PRIMARY KEY (`assessorId`),
  CONSTRAINT `assessor_ibfk_1` FOREIGN KEY (`assessorId`) REFERENCES `user` (`userId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `assessor`
--

LOCK TABLES `assessor` WRITE;
/*!40000 ALTER TABLE `assessor` DISABLE KEYS */;
/*!40000 ALTER TABLE `assessor` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `assessorapplicant`
--

DROP TABLE IF EXISTS `assessorapplicant`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `assessorapplicant` (
  `userId` int DEFAULT NULL COMMENT '用户id，注意此时该用户的角色只能是null',
  `applicationTime` datetime DEFAULT NULL COMMENT '申请时间',
  `categoryId` int DEFAULT NULL,
  `description` varchar(500) DEFAULT NULL COMMENT '个人介绍，有什么资历等',
  `status` enum('待核实','已批准','被拒绝') DEFAULT NULL COMMENT '设置为拒绝或者已批准，向对方手机发送短信',
  KEY `userId` (`userId`),
  KEY `categoryId` (`categoryId`),
  CONSTRAINT `assessorapplicant_ibfk_1` FOREIGN KEY (`userId`) REFERENCES `user` (`userId`),
  CONSTRAINT `assessorapplicant_ibfk_2` FOREIGN KEY (`categoryId`) REFERENCES `category` (`categoryId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `assessorapplicant`
--

LOCK TABLES `assessorapplicant` WRITE;
/*!40000 ALTER TABLE `assessorapplicant` DISABLE KEYS */;
/*!40000 ALTER TABLE `assessorapplicant` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `category`
--

DROP TABLE IF EXISTS `category`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `category` (
  `categoryId` int NOT NULL AUTO_INCREMENT,
  `name` varchar(20) DEFAULT NULL COMMENT '分类名',
  `description` varchar(80) DEFAULT NULL COMMENT '描述',
  PRIMARY KEY (`categoryId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `category`
--

LOCK TABLES `category` WRITE;
/*!40000 ALTER TABLE `category` DISABLE KEYS */;
/*!40000 ALTER TABLE `category` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `log`
--

DROP TABLE IF EXISTS `log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `log` (
  `logId` int NOT NULL AUTO_INCREMENT,
  `operate` varchar(50) DEFAULT NULL,
  `operateTime` datetime DEFAULT NULL,
  PRIMARY KEY (`logId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `log`
--

LOCK TABLES `log` WRITE;
/*!40000 ALTER TABLE `log` DISABLE KEYS */;
/*!40000 ALTER TABLE `log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `manuscript`
--

DROP TABLE IF EXISTS `manuscript`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `manuscript` (
  `manuscriptId` int NOT NULL,
  `description` text COMMENT '稿件摘要或描述',
  `submitTime` datetime DEFAULT NULL COMMENT '用户提交稿件的时间',
  `latestTime` datetime DEFAULT NULL COMMENT '最新修改时间',
  `comment` text COMMENT '稿件审核回复',
  `name` varchar(50) DEFAULT NULL COMMENT '稿件名',
  `path` varchar(500) DEFAULT NULL COMMENT '稿件所在服务器路径',
  `size` int DEFAULT NULL COMMENT '稿件大小',
  `categoryId` int DEFAULT NULL COMMENT '类型Id',
  `status` enum('已公开','已驳回','审核中') DEFAULT NULL COMMENT '稿件状态',
  `writerId` int DEFAULT NULL COMMENT '稿件作者',
  `assessorId` int DEFAULT NULL COMMENT '该稿件的审核员',
  PRIMARY KEY (`manuscriptId`),
  KEY `writerId` (`writerId`),
  KEY `categoryId` (`categoryId`),
  KEY `assessorId` (`assessorId`),
  CONSTRAINT `manuscript_ibfk_1` FOREIGN KEY (`writerId`) REFERENCES `writer` (`writerId`),
  CONSTRAINT `manuscript_ibfk_2` FOREIGN KEY (`categoryId`) REFERENCES `category` (`categoryId`),
  CONSTRAINT `manuscript_ibfk_3` FOREIGN KEY (`assessorId`) REFERENCES `assessor` (`assessorId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `manuscript`
--

LOCK TABLES `manuscript` WRITE;
/*!40000 ALTER TABLE `manuscript` DISABLE KEYS */;
/*!40000 ALTER TABLE `manuscript` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`root`@`localhost`*/ /*!50003 TRIGGER `tri_addManuscript` AFTER INSERT ON `manuscript` FOR EACH ROW begin
	update Writer set manuscriptNumber= manuscriptNumber+1 where writerId=new.writerId;
end */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `notice`
--

DROP TABLE IF EXISTS `notice`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `notice` (
  `noticeId` int NOT NULL AUTO_INCREMENT,
  `publishTime` datetime DEFAULT NULL COMMENT '通知发布时间',
  `latestTime` datetime DEFAULT NULL COMMENT '最新修改时间',
  `title` varchar(20) DEFAULT NULL COMMENT '通知标题',
  `content` text COMMENT '通知内容',
  PRIMARY KEY (`noticeId`),
  UNIQUE KEY `title` (`title`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `notice`
--

LOCK TABLES `notice` WRITE;
/*!40000 ALTER TABLE `notice` DISABLE KEYS */;
/*!40000 ALTER TABLE `notice` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `user` (
  `userId` int NOT NULL AUTO_INCREMENT,
  `role` enum('Writer','Assessor','Admin') DEFAULT NULL COMMENT '角色',
  `nickName` varchar(20) DEFAULT NULL COMMENT '昵称',
  `userName` varchar(20) DEFAULT NULL COMMENT '用户名',
  `password` varchar(20) DEFAULT NULL COMMENT '密码',
  `avatar` varchar(200) DEFAULT NULL COMMENT '头像所在服务器路径',
  `phone` varchar(20) DEFAULT NULL COMMENT '电话',
  PRIMARY KEY (`userId`),
  UNIQUE KEY `userName` (`userName`),
  UNIQUE KEY `nickName` (`nickName`),
  UNIQUE KEY `phone` (`phone`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary view structure for view `view_writeruser`
--

DROP TABLE IF EXISTS `view_writeruser`;
/*!50001 DROP VIEW IF EXISTS `view_writeruser`*/;
SET @saved_cs_client     = @@character_set_client;
/*!50503 SET character_set_client = utf8mb4 */;
/*!50001 CREATE VIEW `view_writeruser` AS SELECT 
 1 AS `userId`,
 1 AS `role`,
 1 AS `nickName`,
 1 AS `userName`,
 1 AS `password`,
 1 AS `avatar`,
 1 AS `phone`,
 1 AS `manuscriptNumber`*/;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `writer`
--

DROP TABLE IF EXISTS `writer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `writer` (
  `writerId` int NOT NULL COMMENT '作者id',
  `manuscriptNumber` int DEFAULT NULL COMMENT '稿件数目',
  PRIMARY KEY (`writerId`),
  CONSTRAINT `writer_ibfk_1` FOREIGN KEY (`writerId`) REFERENCES `user` (`userId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `writer`
--

LOCK TABLES `writer` WRITE;
/*!40000 ALTER TABLE `writer` DISABLE KEYS */;
/*!40000 ALTER TABLE `writer` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Final view structure for view `view_writeruser`
--

/*!50001 DROP VIEW IF EXISTS `view_writeruser`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8mb4 */;
/*!50001 SET character_set_results     = utf8mb4 */;
/*!50001 SET collation_connection      = utf8mb4_0900_ai_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `view_writeruser` AS select `user`.`userId` AS `userId`,`user`.`role` AS `role`,`user`.`nickName` AS `nickName`,`user`.`userName` AS `userName`,`user`.`password` AS `password`,`user`.`avatar` AS `avatar`,`user`.`phone` AS `phone`,`writer`.`manuscriptNumber` AS `manuscriptNumber` from (`user` join `writer` on((`user`.`userId` = `writer`.`writerId`))) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-10-17 21:36:40
