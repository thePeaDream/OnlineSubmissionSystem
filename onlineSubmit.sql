-- MySQL dump 10.13  Distrib 5.7.44, for Linux (x86_64)
--
-- Host: localhost    Database: OnlineSubmitSystem
-- ------------------------------------------------------
-- Server version	5.7.44

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Admin`
--

DROP TABLE IF EXISTS `Admin`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Admin` (
  `adminId` int(11) NOT NULL COMMENT '管理员id',
  PRIMARY KEY (`adminId`),
  CONSTRAINT `Admin_ibfk_1` FOREIGN KEY (`adminId`) REFERENCES `User` (`userId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Admin`
--

LOCK TABLES `Admin` WRITE;
/*!40000 ALTER TABLE `Admin` DISABLE KEYS */;
INSERT INTO `Admin` VALUES (1);
/*!40000 ALTER TABLE `Admin` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Assessor`
--

DROP TABLE IF EXISTS `Assessor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Assessor` (
  `assessorId` int(11) NOT NULL COMMENT '审核id',
  `applicationTime` datetime DEFAULT NULL COMMENT '申请成为审核的时间',
  `description` varchar(400) DEFAULT NULL COMMENT '个人介绍、资历',
  `status` enum('待审批','已通过') DEFAULT NULL,
  `categoryId` int(11) DEFAULT NULL COMMENT '擅长哪一种类别的稿件',
  `pendingAudit` int(11) DEFAULT NULL COMMENT '待审核的稿件数目',
  PRIMARY KEY (`assessorId`),
  KEY `categoryId` (`categoryId`),
  CONSTRAINT `Assessor_ibfk_1` FOREIGN KEY (`assessorId`) REFERENCES `User` (`userId`),
  CONSTRAINT `Assessor_ibfk_2` FOREIGN KEY (`categoryId`) REFERENCES `Category` (`categoryId`) ON DELETE SET NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Assessor`
--

LOCK TABLES `Assessor` WRITE;
/*!40000 ALTER TABLE `Assessor` DISABLE KEYS */;
INSERT INTO `Assessor` VALUES (65,'2024-10-25 08:12:42','审核员3号申请','已通过',33,0),(71,'2024-10-25 13:12:50','我要成为审核员','已通过',34,0),(72,'2024-10-25 19:09:25','你好你好','已通过',34,0),(73,'2024-10-25 19:10:03','nihdwad','已通过',36,0),(75,'2024-10-25 20:22:20','dwdddddddddddddddddd','已通过',37,0),(76,'2024-10-25 20:40:31','dawdada','已通过',33,0),(77,'2024-10-29 12:54:45','dawdawd','待审批',33,0);
/*!40000 ALTER TABLE `Assessor` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`skip-grants user`@`skip-grants host`*/ /*!50003 TRIGGER reset_manuscript_assessorId
BEFORE DELETE ON Assessor
FOR EACH ROW
BEGIN
    
    UPDATE Manuscript
    SET assessorId = -1
    WHERE assessorId = OLD.assessorId;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `Category`
--

DROP TABLE IF EXISTS `Category`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Category` (
  `categoryId` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(20) DEFAULT NULL COMMENT '分类名',
  PRIMARY KEY (`categoryId`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB AUTO_INCREMENT=41 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Category`
--

LOCK TABLES `Category` WRITE;
/*!40000 ALTER TABLE `Category` DISABLE KEYS */;
INSERT INTO `Category` VALUES (39,'dascccc'),(37,'你好daddada'),(38,'你好dawdaw'),(28,'你是'),(30,'你有'),(33,'增加'),(36,'新类型'),(34,'计算机');
/*!40000 ALTER TABLE `Category` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Log`
--

DROP TABLE IF EXISTS `Log`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Log` (
  `logId` int(11) NOT NULL AUTO_INCREMENT,
  `operate` varchar(50) DEFAULT NULL,
  `operateTime` datetime DEFAULT NULL,
  PRIMARY KEY (`logId`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Log`
--

LOCK TABLES `Log` WRITE;
/*!40000 ALTER TABLE `Log` DISABLE KEYS */;
/*!40000 ALTER TABLE `Log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Manuscript`
--

DROP TABLE IF EXISTS `Manuscript`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Manuscript` (
  `manuscriptId` int(11) NOT NULL AUTO_INCREMENT COMMENT '稿件id',
  `description` text COMMENT '稿件内容',
  `submitTime` datetime DEFAULT NULL COMMENT '用户提交稿件的时间',
  `latestTime` datetime DEFAULT NULL COMMENT '最新修改时间',
  `comment` text COMMENT '稿件审核回复',
  `name` varchar(50) DEFAULT NULL COMMENT '稿件名',
  `categoryId` int(11) DEFAULT NULL COMMENT '类型Id',
  `status` enum('Publish','Rejected','UnderReview') DEFAULT NULL COMMENT '稿件状态—已公开、已驳回、审核中',
  `writerId` int(11) DEFAULT NULL COMMENT '稿件作者',
  `assessorId` int(11) DEFAULT '-1',
  PRIMARY KEY (`manuscriptId`),
  KEY `writerId` (`writerId`),
  KEY `categoryId` (`categoryId`),
  KEY `assessorId` (`assessorId`),
  CONSTRAINT `Manuscript_ibfk_1` FOREIGN KEY (`writerId`) REFERENCES `Writer` (`writerId`) ON DELETE SET NULL,
  CONSTRAINT `Manuscript_ibfk_2` FOREIGN KEY (`categoryId`) REFERENCES `Category` (`categoryId`) ON DELETE SET NULL
) ENGINE=InnoDB AUTO_INCREMENT=14 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Manuscript`
--

LOCK TABLES `Manuscript` WRITE;
/*!40000 ALTER TABLE `Manuscript` DISABLE KEYS */;
INSERT INTO `Manuscript` VALUES (1,'feffdacadcdccafesf','2024-10-25 06:19:39','2024-10-25 20:03:13','太少','新稿件的修',34,'UnderReview',53,72),(4,'ndwdaddaddddd','2024-10-25 18:52:31','2024-10-25 20:38:23','ddddad','新的稿件名',34,'UnderReview',53,65),(8,'西悉尼4阿','2024-10-25 19:49:44','2024-10-25 20:36:13','dadwdad','dawdawd',33,'Publish',53,65),(10,'dawdawda','2024-10-25 19:57:41','2024-10-25 19:57:41','','new manuscript',36,'UnderReview',53,71),(11,'dawdadda','2024-10-25 20:01:41','2024-10-25 20:01:41','','new manuscript',34,'UnderReview',53,73),(12,'dadadawwd','2024-10-25 20:18:35','2024-10-25 20:18:35','','新manuscript',36,'UnderReview',53,75),(13,'dwdwdada','2024-10-25 20:37:05','2024-10-25 20:37:05','','daaaaaaaaaaaaaa',36,'UnderReview',53,65);
/*!40000 ALTER TABLE `Manuscript` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`skip-grants user`@`skip-grants host`*/ /*!50003 trigger tri_submitManuscript
after insert on Manuscript
for each row
begin
update Writer set manuscriptNumber= manuscriptNumber+1 where writerId=new.writerId;
end */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`skip-grants user`@`skip-grants host`*/ /*!50003 TRIGGER increase_pending_audit
AFTER UPDATE ON Manuscript
FOR EACH ROW
BEGIN
      IF NEW.assessorId!= OLD.assessorId AND NEW.assessorId!= -1 THEN
        UPDATE Assessor
        SET pendingAudit = pendingAudit + 1
        WHERE assessorId = NEW.assessorId;
    END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`skip-grants user`@`skip-grants host`*/ /*!50003 TRIGGER decrease_pending_audit
AFTER UPDATE ON Manuscript
FOR EACH ROW
BEGIN
       IF (OLD.status = 'UnderReview' AND (NEW.status = 'Publish' OR NEW.status = 'Rejected')) AND OLD.assessorId!= -1 THEN
        UPDATE Assessor
        SET pendingAudit = pendingAudit - 1
        WHERE assessorId = OLD.assessorId;
    END IF;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Table structure for table `Notice`
--

DROP TABLE IF EXISTS `Notice`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Notice` (
  `noticeId` int(11) NOT NULL AUTO_INCREMENT,
  `publishTime` datetime DEFAULT NULL COMMENT '通知发布时间',
  `latestTime` datetime DEFAULT NULL COMMENT '最新修改时间',
  `title` varchar(20) DEFAULT NULL COMMENT '通知标题',
  `content` text COMMENT '通知内容',
  PRIMARY KEY (`noticeId`),
  UNIQUE KEY `title` (`title`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Notice`
--

LOCK TABLES `Notice` WRITE;
/*!40000 ALTER TABLE `Notice` DISABLE KEYS */;
INSERT INTO `Notice` VALUES (9,'2024-10-25 20:41:27','2024-10-25 20:41:27','aaaaaaaaaaaaaaaaa','adwdwda');
/*!40000 ALTER TABLE `Notice` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `User`
--

DROP TABLE IF EXISTS `User`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `User` (
  `userId` int(11) NOT NULL AUTO_INCREMENT,
  `role` enum('Writer','Assessor','Admin') DEFAULT NULL COMMENT '角色',
  `nickName` varchar(20) DEFAULT NULL COMMENT '昵称',
  `userName` varchar(20) DEFAULT NULL COMMENT '用户名',
  `password` varchar(20) DEFAULT NULL COMMENT '密码',
  `phone` varchar(20) DEFAULT NULL COMMENT '电话',
  PRIMARY KEY (`userId`),
  UNIQUE KEY `userName` (`userName`),
  UNIQUE KEY `nickName` (`nickName`),
  UNIQUE KEY `phone` (`phone`)
) ENGINE=InnoDB AUTO_INCREMENT=78 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `User`
--

LOCK TABLES `User` WRITE;
/*!40000 ALTER TABLE `User` DISABLE KEYS */;
INSERT INTO `User` VALUES (1,'Admin','管理员','root','12345678','77916388999'),(53,'Writer','个人新','user','12345678','15916388005'),(65,'Assessor','assessor3','assessor3','12345678','15916344678'),(67,'Writer','user1','user1','12345678','15978964583'),(68,'Writer','user2','user2','12345678','15788653489'),(71,'Assessor','审核员请求3','assessor788','12345678','14798563333'),(72,'Assessor','assessor4','assessor4','123456789','54467892562'),(73,'Assessor','审核员搜索','assessor5','12345678','14568974562'),(75,'Assessor','refsfef','aaa','12345678','14523588962'),(76,'Assessor','aaaaaaaa','aaaaaaaa','12345678','11111111111'),(77,'Assessor','dadwd','newAssessor','12345678','45689522698');
/*!40000 ALTER TABLE `User` ENABLE KEYS */;
UNLOCK TABLES;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
/*!50003 CREATE*/ /*!50017 DEFINER=`skip-grants user`@`skip-grants host`*/ /*!50003 TRIGGER delete_user_manuscripts
BEFORE DELETE ON User
FOR EACH ROW
BEGIN
    DELETE FROM Manuscript
    WHERE writerId = OLD.userId;
END */;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;

--
-- Temporary table structure for view `View_AssessorUser`
--

DROP TABLE IF EXISTS `View_AssessorUser`;
/*!50001 DROP VIEW IF EXISTS `View_AssessorUser`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE VIEW `View_AssessorUser` AS SELECT 
 1 AS `userId`,
 1 AS `role`,
 1 AS `nickName`,
 1 AS `userName`,
 1 AS `password`,
 1 AS `phone`,
 1 AS `applicationTime`,
 1 AS `description`,
 1 AS `status`,
 1 AS `categoryId`,
 1 AS `pendingAudit`*/;
SET character_set_client = @saved_cs_client;

--
-- Temporary table structure for view `View_WriterUser`
--

DROP TABLE IF EXISTS `View_WriterUser`;
/*!50001 DROP VIEW IF EXISTS `View_WriterUser`*/;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
/*!50001 CREATE VIEW `View_WriterUser` AS SELECT 
 1 AS `userId`,
 1 AS `role`,
 1 AS `nickName`,
 1 AS `userName`,
 1 AS `password`,
 1 AS `phone`,
 1 AS `manuscriptNumber`*/;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `Writer`
--

DROP TABLE IF EXISTS `Writer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Writer` (
  `writerId` int(11) NOT NULL COMMENT '作者id',
  `manuscriptNumber` int(11) DEFAULT NULL COMMENT '稿件数目',
  PRIMARY KEY (`writerId`),
  CONSTRAINT `Writer_ibfk_1` FOREIGN KEY (`writerId`) REFERENCES `User` (`userId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Writer`
--

LOCK TABLES `Writer` WRITE;
/*!40000 ALTER TABLE `Writer` DISABLE KEYS */;
INSERT INTO `Writer` VALUES (53,0),(67,0),(68,0);
/*!40000 ALTER TABLE `Writer` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Final view structure for view `View_AssessorUser`
--

/*!50001 DROP VIEW IF EXISTS `View_AssessorUser`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`skip-grants user`@`skip-grants host` SQL SECURITY DEFINER */
/*!50001 VIEW `View_AssessorUser` AS select `User`.`userId` AS `userId`,`User`.`role` AS `role`,`User`.`nickName` AS `nickName`,`User`.`userName` AS `userName`,`User`.`password` AS `password`,`User`.`phone` AS `phone`,`Assessor`.`applicationTime` AS `applicationTime`,`Assessor`.`description` AS `description`,`Assessor`.`status` AS `status`,`Assessor`.`categoryId` AS `categoryId`,`Assessor`.`pendingAudit` AS `pendingAudit` from (`User` join `Assessor` on((`User`.`userId` = `Assessor`.`assessorId`))) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;

--
-- Final view structure for view `View_WriterUser`
--

/*!50001 DROP VIEW IF EXISTS `View_WriterUser`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8 */;
/*!50001 SET character_set_results     = utf8 */;
/*!50001 SET collation_connection      = utf8_general_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`skip-grants user`@`skip-grants host` SQL SECURITY DEFINER */
/*!50001 VIEW `View_WriterUser` AS select `User`.`userId` AS `userId`,`User`.`role` AS `role`,`User`.`nickName` AS `nickName`,`User`.`userName` AS `userName`,`User`.`password` AS `password`,`User`.`phone` AS `phone`,`Writer`.`manuscriptNumber` AS `manuscriptNumber` from (`User` join `Writer` on((`User`.`userId` = `Writer`.`writerId`))) */;
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

-- Dump completed on 2024-10-29 16:19:58
