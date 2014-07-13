*************************** 1. row ***************************
       Table: sd_auxiliary_url_info
Create Table: CREATE TABLE `sd_auxiliary_url_info` (
  `fileUrlNoUP` varchar(255) NOT NULL default '',
  `auxiliaryType` tinyint(3) unsigned NOT NULL default '0',
  `auxiliary` varchar(255) NOT NULL default '',
  `fileSize` bigint(20) unsigned default '0',
  `fileSuffix` varchar(15) default NULL,
  `contentID` varbinary(20) NOT NULL default '',
  `fullContentID` varbinary(20) NOT NULL default '',
  `fullCIDType` tinyint(3) unsigned default '0',
  `fullCIDPartSize` int(11) default '0',
  `lastModified` int(10) unsigned NOT NULL default '0',
  `lastQueryTime` int(11) unsigned default '0',
  PRIMARY KEY  (`fileUrlNoUP`,`auxiliaryType`),
  KEY `auxiliary` (`auxiliary`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_bcid_info_backup
Create Table: CREATE TABLE `sd_bcid_info_backup` (
  `fullContentID` varchar(20) character set latin1 collate latin1_bin NOT NULL default '',
  `blockContentID` mediumblob NOT NULL,
  `lastQueryTime` int(11) unsigned default '0',
  `lastModified` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`fullContentID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_bcid_info
Create Table: CREATE TABLE `sd_bcid_info` (
  `fullContentID` varchar(20) character set latin1 collate latin1_bin NOT NULL default '',
  `blockContentID` mediumblob NOT NULL,
  `lastQueryTime` int(11) unsigned default '0',
  `lastModified` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`fullContentID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_bt_info
Create Table: CREATE TABLE `sd_bt_info` (
  `btInfoID` varchar(20) NOT NULL default '',
  `fileIndex` int(11) NOT NULL default '0',
  `contentID` varchar(20) NOT NULL default '',
  `fileSize` bigint(20) default '0',
  `fullContentID` varchar(20) default NULL,
  `fullCIDType` tinyint(4) default '0',
  `fullCIDVerifyTimes` int(11) default '0',
  `fullCIDConflictTimes` int(11) default '0',
  `fullCIDPartSize` int(11) default '0',
  `queryFlag` int(10) unsigned default '0',
  `lastModified` int(10) unsigned default '0',
  `fileTotalSize` bigint(20) unsigned default NULL,
  `startOffset` bigint(20) unsigned default NULL,
  `blockSize` int(10) unsigned default NULL,
  `lastQueryTime` int(11) unsigned default '0',
  PRIMARY KEY  (`btInfoID`,`fileIndex`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_bt_res
Create Table: CREATE TABLE `sd_bt_res` (
  `contentID` varchar(20) character set latin1 collate latin1_bin NOT NULL default '0',
  `fileSize` bigint(20) unsigned NOT NULL default '0',
  `fullContentID` varchar(20) character set latin1 collate latin1_bin default NULL,
  `btInfoID` varchar(20) character set latin1 collate latin1_bin NOT NULL default '0',
  `fileIndex` int(11) NOT NULL default '0',
  `fileTotalSize` bigint(20) unsigned NOT NULL default '0',
  `startOffset` bigint(20) unsigned NOT NULL default '0',
  `blockSize` int(10) unsigned NOT NULL default '0',
  `lastQueryTime` int(11) unsigned default '0',
  PRIMARY KEY  (`btInfoID`,`fileIndex`),
  KEY `contentID` (`contentID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_cid_pageurl
Create Table: CREATE TABLE `sd_cid_pageurl` (
  `contentID` tinyblob,
  `pageurl` varchar(255) NOT NULL default '',
  `fileurlnoup` varchar(255) NOT NULL default '',
  `lastModified` int(10) unsigned default '0',
  PRIMARY KEY  (`pageurl`),
  KEY `contentID` (`contentID`(20)),
  KEY `contentID_2` (`contentID`(20)),
  KEY `contentID_3` (`contentID`(20))
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_emule_info
Create Table: CREATE TABLE `sd_emule_info` (
  `fileHash` varchar(16) NOT NULL default '',
  `fileSize` bigint(20) NOT NULL default '0',
  `aichHash` varchar(20) default NULL,
  `partHash` mediumblob,
  `fileName` varchar(255) default NULL,
  `contentID` varchar(20) character set latin1 collate latin1_bin NOT NULL default '',
  `fullContentID` varchar(20) character set latin1 collate latin1_bin default NULL,
  `fullCIDType` tinyint(4) default '0',
  `fullCIDPartSize` int(11) default '0',
  `queryFlag` int(11) default '0',
  `lastModified` int(11) default '0',
  `lastQueryTime` int(11) unsigned default '0',
  PRIMARY KEY  (`fileHash`,`fileSize`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_emule_res
Create Table: CREATE TABLE `sd_emule_res` (
  `contentID` varchar(20) character set latin1 collate latin1_bin NOT NULL default '',
  `fileSize` bigint(20) unsigned NOT NULL default '0',
  `fullContentID` varchar(20) character set latin1 collate latin1_bin default NULL,
  `emuleFileHash` varchar(16) NOT NULL default '',
  `lastQueryTime` int(11) unsigned default '0',
  `md5` varchar(16) default NULL,
  PRIMARY KEY  (`emuleFileHash`,`fileSize`),
  KEY `contentID` (`contentID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_gcid_res
Create Table: CREATE TABLE `sd_gcid_res` (
  `contentID` tinyblob,
  `fileSize` bigint(20) unsigned default '0',
  `fullContentID` tinyblob NOT NULL,
  `serverResNum` int(10) unsigned default '0',
  `peerResNum` int(10) unsigned default '0',
  `fullCIDType` tinyint(3) unsigned default '0',
  `PeerDwPercent` tinyint(4) default '-1',
  `fileSuffix` varchar(15) default NULL,
  `lastQueryTime` int(10) unsigned default '0',
  `lastModified` int(10) unsigned default '0',
  PRIMARY KEY  (`fullContentID`(20)),
  KEY `contentID` (`contentID`(20))
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_host_info
Create Table: CREATE TABLE `sd_host_info` (
  `host` varchar(255) NOT NULL default '0',
  `hostSpeed` int(11) default '-1',
  `hostHttpMaxConnection` int(11) default '-1',
  `hostFtpMaxConnection` int(11) default '-1',
  `hostFetchHit` int(11) default '-1',
  `hostMinReTryTimeS` int(11) default '-1',
  `hostConnectTimeMS` int(11) default '-1',
  `lastModified` int(11) default '0',
  `ipAddress` varchar(128) default NULL,
  `userAgent` int(11) NOT NULL default '0',
  `lastQueryTime` int(11) unsigned default '0',
  PRIMARY KEY  (`host`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_md5_info
Create Table: CREATE TABLE `sd_md5_info` (
  `md5` varchar(16) NOT NULL default '',
  `contentID` varchar(20) default NULL,
  `fileSize` bigint(20) unsigned default '0',
  `fullContentID` varchar(20) default NULL,
  `fullCIDType` tinyint(4) default '0',
  `fullCIDPartSize` int(10) unsigned default '0',
  `fileName` varchar(255) default NULL,
  `queryFlag` int(11) default '0',
  `lastModified` int(10) unsigned default '0',
  `lastQueryTime` int(10) unsigned default '0',
  PRIMARY KEY  (`md5`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_real_url_info
Create Table: CREATE TABLE `sd_real_url_info` (
  `fileUrlNoUP` varchar(255) NOT NULL default '',
  `fileSuffix` varchar(15) default NULL,
  `contentID` varchar(20) character set latin1 collate latin1_bin NOT NULL default '',
  `fileSize` bigint(20) unsigned default '0',
  `fullContentID` varchar(20) character set latin1 collate latin1_bin default NULL,
  `fullCIDType` tinyint(3) unsigned default '0',
  `fullCIDVerifyTimes` int(11) default '0',
  `fullCIDConflictTimes` int(11) default '0',
  `fullCIDPartSize` int(11) default '0',
  `queryFlag` int(10) unsigned NOT NULL default '0',
  `lastModified` int(10) unsigned NOT NULL default '0',
  `lastQueryTime` int(11) unsigned default '0',
  `characterUrl` varchar(255) NOT NULL default '',
  PRIMARY KEY  (`fileUrlNoUP`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_real_url_info_long
Create Table: CREATE TABLE `sd_real_url_info_long` (
  `fileUrlHash` bigint(20) unsigned NOT NULL default '0',
  `fileUrlNoUP` text NOT NULL,
  `fileSuffix` varchar(15) default NULL,
  `contentID` varchar(20) character set latin1 collate latin1_bin NOT NULL default '',
  `fileSize` bigint(20) unsigned default '0',
  `fullContentID` varchar(20) character set latin1 collate latin1_bin default NULL,
  `fullCIDType` tinyint(3) unsigned default '0',
  `fullCIDVerifyTimes` int(11) default '0',
  `fullCIDConflictTimes` int(11) default '0',
  `fullCIDPartSize` int(11) default '0',
  `queryFlag` int(10) unsigned NOT NULL default '0',
  `lastModified` int(10) unsigned NOT NULL default '0',
  `lastQueryTime` int(11) unsigned default '0',
  `characterUrl` varchar(255) NOT NULL default '',
  PRIMARY KEY  (`fileUrlHash`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_server_cdn
Create Table: CREATE TABLE `sd_server_cdn` (
  `contentID` varchar(20) character set latin1 collate latin1_bin NOT NULL default '0',
  `fileurlNoUP` text NOT NULL,
  PRIMARY KEY  (`fileurlNoUP`(1000)),
  KEY `contentID` (`contentID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_server_res
Create Table: CREATE TABLE `sd_server_res` (
  `contentID` varchar(20) character set latin1 collate latin1_bin NOT NULL default '0',
  `fileSize` bigint(20) unsigned default '0',
  `fullContentID` varchar(20) character set latin1 collate latin1_bin default NULL,
  `fileUrl` varchar(255) NOT NULL default '',
  `fileUrlNoUP` varchar(255) NOT NULL default '0',
  `pageUrl` varchar(255) default NULL,
  `urlQuality` tinyint(4) default '1',
  `lastValidTime` int(11) unsigned default '0',
  `firstInvalidTime` int(10) unsigned default '0',
  `invalidTimes` smallint(5) unsigned default '0',
  `lastQueryTime` int(11) unsigned default '0',
  `fileUrlCodePage` int(11) default '-2',
  `pageUrlCodePage` int(11) default '-2',
  PRIMARY KEY  (`fileUrlNoUP`),
  KEY `contentID` (`contentID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_server_res_long
Create Table: CREATE TABLE `sd_server_res_long` (
  `fileUrlHash` bigint(20) unsigned NOT NULL default '0',
  `contentID` varchar(20) character set latin1 collate latin1_bin NOT NULL default '0',
  `fileSize` bigint(20) unsigned default '0',
  `fullContentID` varchar(20) character set latin1 collate latin1_bin default NULL,
  `fileUrl` text NOT NULL,
  `fileUrlNoUP` text NOT NULL,
  `pageUrl` varchar(255) default NULL,
  `urlQuality` tinyint(4) default '1',
  `lastValidTime` int(11) unsigned default '0',
  `firstInvalidTime` int(10) unsigned default '0',
  `invalidTimes` smallint(5) unsigned default '0',
  `lastQueryTime` int(11) unsigned default '0',
  `fileUrlCodePage` int(11) default '-1',
  `pageUrlCodePage` int(11) default '-1',
  PRIMARY KEY  (`fileUrlHash`),
  KEY `contentID` (`contentID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_session_url_info
Create Table: CREATE TABLE `sd_session_url_info` (
  `fileUrlNoUP` varchar(255) NOT NULL default '',
  `fileSuffix` varchar(15) default NULL,
  `contentID` varchar(20) character set latin1 collate latin1_bin NOT NULL default '',
  `fileSize` bigint(20) unsigned default '0',
  `fullContentID` varchar(20) character set latin1 collate latin1_bin default NULL,
  `fullCIDType` tinyint(3) unsigned default '0',
  `fullCIDVerifyTimes` int(11) default '0',
  `fullCIDConflictTimes` int(11) default '0',
  `fullCIDPartSize` int(11) default '0',
  `queryFlag` int(10) unsigned NOT NULL default '0',
  `lastModified` int(10) unsigned NOT NULL default '0',
  `lastQueryTime` int(11) unsigned default '0',
  PRIMARY KEY  (`fileUrlNoUP`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_session_url_info_long
Create Table: CREATE TABLE `sd_session_url_info_long` (
  `fileUrlHash` bigint(20) unsigned NOT NULL default '0',
  `fileUrlNoUP` text NOT NULL,
  `fileSuffix` varchar(15) default NULL,
  `contentID` varchar(20) character set latin1 collate latin1_bin NOT NULL default '',
  `fileSize` bigint(20) unsigned default '0',
  `fullContentID` varchar(20) character set latin1 collate latin1_bin default NULL,
  `fullCIDType` tinyint(3) unsigned default '0',
  `fullCIDVerifyTimes` int(11) default '0',
  `fullCIDConflictTimes` int(11) default '0',
  `fullCIDPartSize` int(11) default '0',
  `queryFlag` int(10) unsigned NOT NULL default '0',
  `lastModified` int(10) unsigned NOT NULL default '0',
  `lastQueryTime` int(11) unsigned default '0',
  PRIMARY KEY  (`fileUrlHash`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_url_hash_info
Create Table: CREATE TABLE `sd_url_hash_info` (
  `hashValue` bigint(20) unsigned NOT NULL default '0',
  `lastModified` int(10) unsigned default '0',
  PRIMARY KEY  (`hashValue`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_url_info_backup
Create Table: CREATE TABLE `sd_url_info_backup` (
  `fileUrlNoUP` varchar(255) NOT NULL default '',
  `fileSuffix` varchar(15) default NULL,
  `contentID` varchar(20) character set latin1 collate latin1_bin NOT NULL default '',
  `fileSize` bigint(20) unsigned default '0',
  `fullContentID` varchar(20) character set latin1 collate latin1_bin default NULL,
  `fullCIDType` tinyint(3) unsigned default '0',
  `fullCIDVerifyTimes` int(11) default '0',
  `fullCIDConflictTimes` int(11) default '0',
  `fullCIDPartSize` int(11) default '0',
  `queryFlag` int(10) unsigned NOT NULL default '0',
  `lastModified` int(10) unsigned NOT NULL default '0',
  `lastQueryTime` int(11) unsigned default '0',
  PRIMARY KEY  (`fileUrlNoUP`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_url_info
Create Table: CREATE TABLE `sd_url_info` (
  `fileUrlNoUP` varchar(255) NOT NULL default '',
  `fileSuffix` varchar(15) default NULL,
  `contentID` varchar(20) character set latin1 collate latin1_bin NOT NULL default '',
  `fileSize` bigint(20) unsigned default '0',
  `fullContentID` varchar(20) character set latin1 collate latin1_bin default NULL,
  `fullCIDType` tinyint(3) unsigned default '0',
  `fullCIDVerifyTimes` int(11) default '0',
  `fullCIDConflictTimes` int(11) default '0',
  `fullCIDPartSize` int(11) default '0',
  `queryFlag` int(10) unsigned NOT NULL default '0',
  `lastModified` int(10) unsigned NOT NULL default '0',
  `lastQueryTime` int(11) unsigned default '0',
  PRIMARY KEY  (`fileUrlNoUP`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_url_info_long
Create Table: CREATE TABLE `sd_url_info_long` (
  `fileUrlHash` bigint(20) unsigned NOT NULL default '0',
  `fileUrlNoUP` text NOT NULL,
  `fileSuffix` varchar(15) default NULL,
  `contentID` varchar(20) character set latin1 collate latin1_bin NOT NULL default '',
  `fileSize` bigint(20) unsigned default '0',
  `fullContentID` varchar(20) character set latin1 collate latin1_bin default NULL,
  `fullCIDType` tinyint(3) unsigned default '0',
  `fullCIDVerifyTimes` int(11) default '0',
  `fullCIDConflictTimes` int(11) default '0',
  `fullCIDPartSize` int(11) default '0',
  `queryFlag` int(10) unsigned NOT NULL default '0',
  `lastModified` int(10) unsigned NOT NULL default '0',
  `lastQueryTime` int(11) unsigned default '0',
  PRIMARY KEY  (`fileUrlHash`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_url_info_long_modify
Create Table: CREATE TABLE `sd_url_info_long_modify` (
  `fileUrlHash` bigint(20) unsigned default '0',
  `fileUrlNoUP` text,
  `fileUrlNoUPCodePage` int(11) default '-2',
  `fileSuffix` varchar(15) default NULL,
  `contentID` varchar(20) character set latin1 collate latin1_bin NOT NULL default '',
  `fileSize` bigint(20) unsigned default '0',
  `fullContentID` varchar(20) character set latin1 collate latin1_bin default NULL,
  `fullCIDType` tinyint(3) unsigned default '0',
  `fullCIDVerifyTimes` int(11) default '0',
  `fullCIDConflictTimes` int(11) default '0',
  `fullCIDPartSize` int(11) default '0',
  `queryFlag` int(10) unsigned NOT NULL default '0',
  `lastModified` int(10) unsigned NOT NULL default '0',
  `lastQueryTime` int(11) unsigned default '0',
  `isUTF8` tinyint(4) default '0',
  KEY `fileUrlHash` (`fileUrlHash`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_url_info_long_utf8
Create Table: CREATE TABLE `sd_url_info_long_utf8` (
  `fileUrlHash` bigint(20) unsigned NOT NULL default '0',
  `fileUrlNoUP` text NOT NULL,
  `fileUrlNoUPCodePage` int(11) default '-2',
  `fileSuffix` varchar(15) default NULL,
  `contentID` varchar(20) character set latin1 collate latin1_bin NOT NULL default '',
  `fileSize` bigint(20) unsigned default '0',
  `fullContentID` varchar(20) character set latin1 collate latin1_bin default NULL,
  `fullCIDType` tinyint(3) unsigned default '0',
  `fullCIDVerifyTimes` int(11) default '0',
  `fullCIDConflictTimes` int(11) default '0',
  `fullCIDPartSize` int(11) default '0',
  `queryFlag` int(10) unsigned NOT NULL default '0',
  `lastModified` int(10) unsigned NOT NULL default '0',
  `lastQueryTime` int(11) unsigned default '0',
  PRIMARY KEY  (`fileUrlHash`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_url_info_modify
Create Table: CREATE TABLE `sd_url_info_modify` (
  `fileUrlNoUP` varchar(255) NOT NULL default '',
  `fileUrlNoUPCodePage` int(11) default '-2',
  `fileSuffix` varchar(15) default NULL,
  `contentID` varchar(20) character set latin1 collate latin1_bin NOT NULL default '',
  `fileSize` bigint(20) unsigned default '0',
  `fullContentID` varchar(20) character set latin1 collate latin1_bin default NULL,
  `fullCIDType` tinyint(3) unsigned default '0',
  `fullCIDVerifyTimes` int(11) default '0',
  `fullCIDConflictTimes` int(11) default '0',
  `fullCIDPartSize` int(11) default '0',
  `queryFlag` int(10) unsigned NOT NULL default '0',
  `lastModified` int(10) unsigned NOT NULL default '0',
  `lastQueryTime` int(11) unsigned default '0',
  `isUTF8` tinyint(4) default '0',
  KEY `fileUrlNoUP` (`fileUrlNoUP`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
*************************** 1. row ***************************
       Table: sd_url_info_utf8
Create Table: CREATE TABLE `sd_url_info_utf8` (
  `fileUrlNoUP` varchar(255) NOT NULL default '',
  `fileUrlNoUPCodePage` int(11) default '-2',
  `fileSuffix` varchar(15) default NULL,
  `contentID` varchar(20) character set latin1 collate latin1_bin NOT NULL default '',
  `fileSize` bigint(20) unsigned default '0',
  `fullContentID` varchar(20) character set latin1 collate latin1_bin default NULL,
  `fullCIDType` tinyint(3) unsigned default '0',
  `fullCIDVerifyTimes` int(11) default '0',
  `fullCIDConflictTimes` int(11) default '0',
  `fullCIDPartSize` int(11) default '0',
  `queryFlag` int(10) unsigned NOT NULL default '0',
  `lastModified` int(10) unsigned NOT NULL default '0',
  `lastQueryTime` int(11) unsigned default '0',
  PRIMARY KEY  (`fileUrlNoUP`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1
