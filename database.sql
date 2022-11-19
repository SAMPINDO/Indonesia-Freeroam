-- MariaDB dump 10.19  Distrib 10.5.10-MariaDB, for Win64 (AMD64)
--
-- Host: 127.0.0.1    Database: ifr
-- ------------------------------------------------------
-- Server version	10.5.10-MariaDB-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `accounts`
--

DROP TABLE IF EXISTS `accounts`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `accounts` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(24) NOT NULL,
  `password` varchar(60) DEFAULT NULL,
  `email` varchar(255) DEFAULT NULL,
  `discord_id` varchar(20) DEFAULT NULL,
  `discord_bound_at` int(11) DEFAULT 0,
  `admin_level` int(2) NOT NULL DEFAULT 0,
  `money` int(10) NOT NULL DEFAULT 0,
  `bank` int(10) NOT NULL DEFAULT 0,
  `level` int(4) NOT NULL DEFAULT 0,
  `exp` int(6) NOT NULL DEFAULT 0,
  `kills` int(9) NOT NULL DEFAULT 0,
  `deaths` int(9) NOT NULL DEFAULT 0,
  `model_skin_id` int(4) NOT NULL DEFAULT 7,
  `play_time` int(10) NOT NULL DEFAULT 0,
  `vip_level` int(2) NOT NULL DEFAULT 0,
  `vip_expired_at` int(10) NOT NULL DEFAULT 0,
  `registered_at` int(10) NOT NULL DEFAULT 0,
  `created_at` int(10) NOT NULL DEFAULT 0,
  `updated_at` int(10) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`),
  UNIQUE KEY `accounts_username_IDX` (`username`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `bans`
--

DROP TABLE IF EXISTS `bans`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `bans` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `issuer_id` int(11) NOT NULL,
  `issuer_name` varchar(24) NOT NULL,
  `issuer_ip_address` varchar(15) NOT NULL DEFAULT '255.255.255.255',
  `target_id` int(11) NOT NULL,
  `target_name` varchar(24) NOT NULL,
  `target_ip_address` varchar(15) NOT NULL DEFAULT '255.255.255.255',
  `reason` varchar(255) NOT NULL,
  `created_at` int(10) NOT NULL DEFAULT 0,
  `expired_at` int(10) NOT NULL DEFAULT 0,
  `is_permanent` tinyint(1) NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`),
  KEY `bans_issuer_FK` (`issuer_id`),
  KEY `bans_target_FK` (`target_id`),
  CONSTRAINT `bans_issuer_FK` FOREIGN KEY (`issuer_id`) REFERENCES `accounts` (`id`),
  CONSTRAINT `bans_target_FK` FOREIGN KEY (`target_id`) REFERENCES `accounts` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping routines for database 'ifr'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-11-19 16:36:57
