
/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

CREATE TABLE IF NOT EXISTS `galaxy` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `primary_id` int(11) DEFAULT NULL,
  `name` varchar(100) NOT NULL,
  `version` varchar(100) NOT NULL,
  `status` int(11) NOT NULL,
  `created_at` datetime NOT NULL,
  `updated_at` datetime NOT NULL,
  PRIMARY KEY (`id`),
  KEY `IDX_F6BB137621DE0C6C` (`primary_id`),
  CONSTRAINT `FK_F6BB137621DE0C6C` FOREIGN KEY (`primary_id`) REFERENCES `service` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;

DELETE FROM `galaxy`;
    
/*!40000 ALTER TABLE `galaxy` DISABLE KEYS */;
INSERT INTO `galaxy` (`id`, `primary_id`, `name`, `version`, `status`, `created_at`, `updated_at`) VALUES
	(1, NULL, 'A New Hope', '', 2, '2011-10-14 17:14:13', '2011-10-14 17:14:13');
/*!40000 ALTER TABLE `galaxy` ENABLE KEYS */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
