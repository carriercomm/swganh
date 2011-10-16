# --------------------------------------------------------
# Host:                         127.0.0.1
# Server version:               5.3.1-MariaDB
# Server OS:                    Win32
# HeidiSQL version:             6.0.0.3603
# Date/time:                    2011-10-15 14:37:15
# --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

# Dumping structure for table galaxy.player_session
CREATE TABLE IF NOT EXISTS `player_session` (
  `id` bigint(20) NOT NULL AUTO_INCREMENT,
  `player` int(11) NOT NULL,
  `session_key` varchar(100) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=33 DEFAULT CHARSET=latin1;

# Dumping data for table galaxy.player_session: ~21 rows (approximately)
DELETE FROM `player_session`;
/*!40000 ALTER TABLE `player_session` DISABLE KEYS */;
INSERT INTO `player_session` (`id`, `player`, `session_key`) VALUES
	(1, 2, '2011-Oct-15 10:34:12.860786583892433'),
	(2, 2, '2011-Oct-15 11:00:04.2395191911554948'),
	(3, 2, '2011-Oct-15 11:01:58.578059108479490'),
	(4, 2, '2011-Oct-15 11:17:55.731805650786457'),
	(5, 2, '2011-Oct-15 12:05:00.5653771487939274'),
	(6, 2, '2011-Oct-15 12:08:01.1237042075744114'),
	(7, 2, '2011-Oct-15 12:49:19.1854411764510336'),
	(8, 2, '2011-Oct-15 12:50:48.2655361754873045'),
	(9, 2, '2011-Oct-15 12:57:43.378279915998978'),
	(10, 2, '2011-Oct-15 13:04:25.911303334053504'),
	(11, 2, '2011-Oct-15 13:04:47.329528600393932'),
	(12, 2, '2011-Oct-15 13:12:56.993535264187668'),
	(13, 2, '2011-Oct-15 13:25:08.7733901110267100'),
	(14, 2, '2011-Oct-15 13:29:54.992761915279206'),
	(15, 2, '2011-Oct-15 13:34:00.0257761180118089'),
	(16, 2, '2011-Oct-15 13:34:36.1828441818830991'),
	(17, 2, '2011-Oct-15 13:35:04.8634852110858782'),
	(18, 2, '2011-Oct-15 13:35:18.211248420897138'),
	(19, 2, '2011-Oct-15 13:36:13.7594251075671536'),
	(20, 2, '2011-Oct-15 14:02:35.2878841229588087'),
	(21, 2, '2011-Oct-15 14:19:14.2210191810387001'),
	(22, 2, '2011-Oct-15 14:20:48.4774101412176211'),
	(23, 2, '2011-Oct-15 14:22:15.2193721808469961'),
	(24, 2, '2011-Oct-15 14:22:24.514903674461812'),
	(25, 2, '2011-Oct-15 14:22:35.389525614345484'),
	(26, 2, '2011-Oct-15 14:22:51.2714341792301727'),
	(27, 2, '2011-Oct-15 14:23:45.498535542708350'),
	(28, 2, '2011-Oct-15 14:24:34.3233283475407'),
	(29, 2, '2011-Oct-15 14:24:45.657976452202188'),
	(30, 2, '2011-Oct-15 14:24:57.475652244333101'),
	(31, 2, '2011-Oct-15 14:27:15.7725621167001973'),
	(32, 2, '2011-Oct-15 14:35:10.1146931495082282');
/*!40000 ALTER TABLE `player_session` ENABLE KEYS */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;