DROP DATABASE IF EXISTS `metro`;
CREATE DATABASE IF NOT EXISTS `metro` DEFAULT CHARACTER SET utf8;

USE `metro`;

DROP TABLE IF EXISTS `MetroLine`;
CREATE TABLE `MetroLine` (
  `MetroLineID` bigint(20) NOT NULL AUTO_INCREMENT,
  `Name` varchar(64) NOT NULL DEFAULT '',
  PRIMARY KEY (`MetroLineID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `MetroStation`;
CREATE TABLE `MetroStation` (
  `MetroStationID` bigint(20) NOT NULL AUTO_INCREMENT,
  `MetroLineID` bigint(20) NOT NULL,
  `Name` varchar(64) NOT NULL DEFAULT '',
  PRIMARY KEY (`MetroStationID`),
  KEY `MetroLineID` (`MetroLineID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `TransferHub`;
CREATE TABLE `TransferHub` (
  `TransferHubID` bigint(20) NOT NULL AUTO_INCREMENT,
  `StartsMetroStationID` bigint(20) NOT NULL,
  `EndsMetroStationID` bigint(20) NOT NULL,
  PRIMARY KEY (`TransferHubID`),
  KEY `StartsMetroStationID` (`StartsMetroStationID`),
  KEY `EndsMetroStationID` (`EndsMetroStationID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `TurnstileRecord`;
CREATE TABLE `TurnstileRecord` (
  `TurnstileRecordID` bigint(20) NOT NULL AUTO_INCREMENT,
  `MetroStationID` bigint(20) NOT NULL,
  `Status` tinyint(4) NOT NULL DEFAULT '0',
  `Date` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`TurnstileRecordID`),
  KEY `MetroStationID` (`MetroStationID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
