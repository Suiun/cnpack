-- phpMyAdmin SQL Dump
-- version 2.11.9.5
-- http://www.phpmyadmin.net
--
-- ����: localhost
-- ��������: 2012 �� 11 �� 26 �� 16:23
-- �������汾: 5.1.37
-- PHP �汾: 5.2.10

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

--
-- ���ݿ�: `test`
--

-- --------------------------------------------------------

--
-- ��Ľṹ `cwcntcountry`
--

CREATE TABLE IF NOT EXISTS `cwcntcountry` (
  `id` varchar(64) NOT NULL DEFAULT '',
  `date` date NOT NULL DEFAULT '0000-00-00',
  `code` char(2) NOT NULL DEFAULT '',
  `count` int(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `code` (`code`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- ��Ľṹ `cwcnthour`
--

CREATE TABLE IF NOT EXISTS `cwcnthour` (
  `id` varchar(64) NOT NULL DEFAULT '',
  `date` date NOT NULL DEFAULT '0000-00-00',
  `hour` int(4) NOT NULL DEFAULT '0',
  `count` int(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- ��Ľṹ `cwcntide`
--

CREATE TABLE IF NOT EXISTS `cwcntide` (
  `id` varchar(64) NOT NULL DEFAULT '',
  `date` date NOT NULL DEFAULT '0000-00-00',
  `ide` varchar(32) NOT NULL DEFAULT '',
  `count` int(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `ide` (`ide`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- ��Ľṹ `cwcntlang`
--

CREATE TABLE IF NOT EXISTS `cwcntlang` (
  `id` varchar(64) NOT NULL DEFAULT '',
  `date` date NOT NULL DEFAULT '0000-00-00',
  `lang` char(4) NOT NULL DEFAULT '',
  `count` int(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `lang` (`lang`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- ��Ľṹ `cwcntmonth`
--

CREATE TABLE IF NOT EXISTS `cwcntmonth` (
  `id` varchar(64) NOT NULL DEFAULT '',
  `date` date NOT NULL DEFAULT '0000-00-00',
  `count` int(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- ��Ľṹ `cwcntunion`
--

CREATE TABLE IF NOT EXISTS `cwcntunion` (
  `id` varchar(255) NOT NULL DEFAULT '',
  `date` date NOT NULL DEFAULT '0000-00-00',
  `ide` varchar(32) NOT NULL DEFAULT '',
  `ver` varchar(32) NOT NULL DEFAULT '',
  `code` char(2) NOT NULL DEFAULT '',
  `count` int(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- ��Ľṹ `cwcntver`
--

CREATE TABLE IF NOT EXISTS `cwcntver` (
  `id` varchar(64) NOT NULL DEFAULT '',
  `date` date NOT NULL DEFAULT '0000-00-00',
  `ver` varchar(32) NOT NULL DEFAULT '',
  `count` int(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `ver` (`ver`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- ��Ľṹ `cwconfig`
--

CREATE TABLE IF NOT EXISTS `cwconfig` (
  `name` varchar(32) NOT NULL DEFAULT '',
  `value` varchar(255) NOT NULL DEFAULT '',
  PRIMARY KEY (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- ��Ľṹ `cwdictionary`
--

CREATE TABLE IF NOT EXISTS `cwdictionary` (
  `name` varchar(32) NOT NULL DEFAULT '',
  `value` varchar(255) NOT NULL DEFAULT '',
  PRIMARY KEY (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- ��Ľṹ `cwlogs`
--

CREATE TABLE IF NOT EXISTS `cwlogs` (
  `ipaddr` varchar(32) NOT NULL DEFAULT '',
  `date` datetime NOT NULL,
  `ide` varchar(32) NOT NULL DEFAULT '',
  `ver` varchar(32) NOT NULL DEFAULT '',
  `code` char(2) NOT NULL DEFAULT '',
  `lang` char(4) NOT NULL DEFAULT ''
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
