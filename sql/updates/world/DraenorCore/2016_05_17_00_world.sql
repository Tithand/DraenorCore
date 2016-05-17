
UPDATE `creature_template` SET `lootID`='40123' WHERE `entry`='40123';
UPDATE `creature_template` SET `lootID`='39436' WHERE `entry`='39436';
DELETE FROM `creature_loot_template` WHERE `entry` IN ('40123', '39436');
INSERT INTO `creature_loot_template` (`entry`,`Item`,`Chance`,`GroupId`,`MinCount`,`MaxCount`) values
(40123, '52370', '0.0042', '0', '1','1'),
(40123, '52385', '0.0101', '0', '1','1'),
(40123, '53010', '16.7226', '0', '1','2'),
(40123, '55281', '0.0076', '0', '1','1'),
(40123, '55282', '0.005', '0', '1','1'),
(40123, '55283', '0.005', '0', '1','1'),
(40123, '55290', '0.0084', '0', '1','1'),
(40123, '55291', '0.0042', '0', '1','1'),
(40123, '55308', '0.0185', '0', '1','1'),
(40123, '55309', '0.0135', '0', '1','1'),
(40123, '55310', '0.021', '0', '1','1'),
(40123, '55326', '0.0084', '0', '1','1'),
(40123, '55327', '0.0101', '0', '1','1'),
(40123, '55328', '0.0042', '0', '1','1'),
(40123, '55336', '0.016', '0', '1','1'),
(40123, '55337', '0.0084', '0', '1','1'),
(40123, '55346', '0.0076', '0', '1','1'),
(40123, '55362', '0.0143', '0', '1','1'),
(40123, '55363', '0.0168', '0', '1','1'),
(40123, '55364', '0.0143', '0', '1','1'),
(40123, '55372', '0.0067', '0', '1','1'),
(40123, '55373', '0.0101', '0', '1','1'),
(40123, '55380', '0.0042', '0', '1','1'),
(40123, '55381', '0.0109', '0', '1','1'),
(40123, '55382', '0.0042', '0', '1','1'),
(40123, '55389', '0.0059', '0', '1','1'),
(40123, '55391', '0.0059', '0', '1','1'),
(40123, '55398', '0.0244', '0', '1','1'),
(40123, '55399', '0.0168', '0', '1','1'),
(40123, '55400', '0.0177', '0', '1','1'),
(40123, '55416', '0.1009', '0', '1','1'),
(40123, '55417', '0.0437', '0', '1','1'),
(40123, '55418', '0.0362', '0', '1','1'),
(40123, '55425', '0.0177', '0', '1','1'),
(40123, '55426', '0.0101', '0', '1','1'),
(40123, '55427', '0.0067', '0', '1','1'),
(40123, '55434', '0.0202', '0', '1','1'),
(40123, '55435', '0.0362', '0', '1','1'),
(40123, '55436', '0.0345', '0', '1','1'),
(40123, '55452', '0.0059', '0', '1','1'),
(40123, '55453', '0.0109', '0', '1','1'),
(40123, '55461', '0.005', '0', '1','1'),
(40123, '55463', '0.0067', '0', '1','1'),
(40123, '55479', '0.0235', '0', '1','1'),
(40123, '55480', '0.0311', '0', '1','1'),
(40123, '55481', '0.016', '0', '1','1'),
(40123, '55488', '0.021', '0', '1','1'),
(40123, '55489', '0.0151', '0', '1','1'),
(40123, '55490', '0.0101', '0', '1','1'),
(40123, '55497', '0.0235', '0', '1','1'),
(40123, '55498', '0.0135', '0', '1','1'),
(40123, '55499', '0.0126', '0', '1','1'),
(40123, '55506', '0.0126', '0', '1','1'),
(40123, '55507', '0.0177', '0', '1','1'),
(40123, '55508', '0.0109', '0', '1','1'),
(40123, '55515', '0.0135', '0', '1','1'),
(40123, '55516', '0.0235', '0', '1','1'),
(40123, '55517', '0.0219', '0', '1','1'),
(40123, '55524', '0.0151', '0', '1','1'),
(40123, '55525', '0.0151', '0', '1','1'),
(40123, '55526', '0.021', '0', '1','1'),
(40123, '55533', '0.0151', '0', '1','1'),
(40123, '55534', '0.0193', '0', '1','1'),
(40123, '55535', '0.0168', '0', '1','1'),
(40123, '55542', '0.0151', '0', '1','1'),
(40123, '55543', '0.0093', '0', '1','1'),
(40123, '55544', '0.0252', '0', '1','1'),
(40123, '55551', '0.0235', '0', '1','1'),
(40123, '55552', '0.0118', '0', '1','1'),
(40123, '55553', '0.0093', '0', '1','1'),
(40123, '55560', '0.0135', '0', '1','1'),
(40123, '55561', '0.0235', '0', '1','1'),
(40123, '55562', '0.0235', '0', '1','1'),
(40123, '55569', '0.0093', '0', '1','1'),
(40123, '55570', '0.0143', '0', '1','1'),
(40123, '55571', '0.016', '0', '1','1'),
(40123, '55578', '0.0118', '0', '1','1'),
(40123, '55580', '0.0143', '0', '1','1'),
(40123, '55587', '0.0143', '0', '1','1'),
(40123, '55588', '0.016', '0', '1','1'),
(40123, '55589', '0.0193', '0', '1','1'),
(40123, '55596', '0.0168', '0', '1','1'),
(40123, '55597', '0.0185', '0', '1','1'),
(40123, '55598', '0.021', '0', '1','1'),
(40123, '55605', '0.0177', '0', '1','1'),
(40123, '55606', '0.0067', '0', '1','1'),
(40123, '55607', '0.0151', '0', '1','1'),
(40123, '55614', '0.0109', '0', '1','1'),
(40123, '55615', '0.0185', '0', '1','1'),
(40123, '55616', '0.0151', '0', '1','1'),
(40123, '55623', '0.0177', '0', '1','1'),
(40123, '55624', '0.0109', '0', '1','1'),
(40123, '55625', '0.0185', '0', '1','1'),
(40123, '55632', '0.016', '0', '1','1'),
(40123, '55633', '0.0109', '0', '1','1'),
(40123, '55634', '0.0227', '0', '1','1'),
(40123, '55641', '0.0135', '0', '1','1'),
(40123, '55642', '0.016', '0', '1','1'),
(40123, '55643', '0.0664', '0', '1','1'),
(40123, '55650', '0.0109', '0', '1','1'),
(40123, '55651', '0.0278', '0', '1','1'),
(40123, '55659', '0.0177', '0', '1','1'),
(40123, '55660', '0.0202', '0', '1','1'),
(40123, '55661', '0.0219', '0', '1','1'),
(40123, '55668', '0.0177', '0', '1','1'),
(40123, '55669', '0.0479', '0', '1','1'),
(40123, '55670', '0.0101', '0', '1','1'),
(40123, '55677', '0.0151', '0', '1','1'),
(40123, '55678', '0.016', '0', '1','1'),
(40123, '55679', '0.0143', '0', '1','1'),
(40123, '55686', '0.0202', '0', '1','1'),
(40123, '55687', '0.0076', '0', '1','1'),
(40123, '55688', '0.0109', '0', '1','1'),
(40123, '55695', '0.0135', '0', '1','1'),
(40123, '55696', '0.0126', '0', '1','1'),
(40123, '55697', '0.0076', '0', '1','1'),
(40123, '55704', '0.0202', '0', '1','1'),
(40123, '55705', '0.0252', '0', '1','1'),
(40123, '55706', '0.0193', '0', '1','1'),
(40123, '55713', '0.0269', '0', '1','1'),
(40123, '55714', '0.0278', '0', '1','1'),
(40123, '55715', '0.0219', '0', '1','1'),
(40123, '55722', '0.0496', '0', '1','1'),
(40123, '55723', '0.021', '0', '1','1'),
(40123, '55724', '0.0227', '0', '1','1'),
(40123, '55731', '0.042', '0', '1','1'),
(40123, '55732', '0.0303', '0', '1','1'),
(40123, '55733', '0.0202', '0', '1','1'),
(40123, '55740', '0.0151', '0', '1','1'),
(40123, '55741', '0.0101', '0', '1','1'),
(40123, '55742', '0.0252', '0', '1','1'),
(40123, '55749', '0.037', '0', '1','1'),
(40123, '55750', '0.0177', '0', '1','1'),
(40123, '55751', '0.0185', '0', '1','1'),
(40123, '55758', '0.0294', '0', '1','1'),
(40123, '55759', '0.0294', '0', '1','1'),
(40123, '55760', '0.0278', '0', '1','1'),
(40123, '55767', '0.0362', '0', '1','1'),
(40123, '55768', '0.0227', '0', '1','1'),
(40123, '55769', '0.0193', '0', '1','1'),
(40123, '58256', '2.8156', '0', '1','1'),
(40123, '58268', '5.5016', '0', '1','1'),
(40123, '62063', '0.0748', '0', '1','1'),
(40123, '62064', '0.0471', '0', '1','1'),
(40123, '62065', '0.0706', '0', '1','1'),
(40123, '62066', '0.0488', '0', '1','1'),
(40123, '62067', '0.0681', '0', '1','1'),
(40123, '62068', '0.1211', '0', '1','1'),
(40123, '62069', '0.0748', '0', '1','1'),
(40123, '62070', '0.0412', '0', '1','1'),
(40123, '62071', '0.0681', '0', '1','1'),
(40123, '62072', '0.0723', '0', '1','1'),
(40123, '62073', '0.0782', '0', '1','1'),
(40123, '62074', '0.0866', '0', '1','1'),
(40123, '62075', '0.1076', '0', '1','1'),
(40123, '62076', '0.0732', '0', '1','1'),
(40123, '62077', '0.0849', '0', '1','1'),
(40123, '62078', '0.0816', '0', '1','1'),
(40123, '62079', '0.0875', '0', '1','1'),
(40123, '62080', '0.074', '0', '1','1'),
(40123, '62081', '0.1085', '0', '1','1'),
(40123, '62082', '0.1093', '0', '1','1'),
(40123, '62083', '0.0917', '0', '1','1'),
(40123, '62084', '0.0648', '0', '1','1'),
(40123, '62085', '0.1018', '0', '1','1'),
(40123, '62086', '0.0875', '0', '1','1'),
(40123, '62087', '0.0816', '0', '1','1'),
(40123, '62088', '0.0866', '0', '1','1'),
(40123, '62089', '0.0706', '0', '1','1'),
(40123, '62090', '0.1228', '0', '1','1'),
(40123, '62091', '0.095', '0', '1','1'),
(40123, '62092', '0.0833', '0', '1','1'),
(40123, '62093', '0.069', '0', '1','1'),
(40123, '62094', '0.0816', '0', '1','1'),
(40123, '62095', '0.1026', '0', '1','1'),
(40123, '62096', '0.106', '0', '1','1'),
(40123, '62097', '0.1076', '0', '1','1'),
(40123, '62098', '0.0833', '0', '1','1'),
(40123, '62099', '0.0673', '0', '1','1'),
(40123, '62100', '0.0866', '0', '1','1'),
(40123, '62101', '0.074', '0', '1','1'),
(40123, '62102', '0.0891', '0', '1','1'),
(40123, '62103', '0.0723', '0', '1','1'),
(40123, '62104', '0.0681', '0', '1','1'),
(40123, '67099', '0.0109', '0', '1','1'),
(40123, '67103', '0.0067', '0', '1','1'),
(40123, '67539', '0.4163', '0', '1','1'),
(40123, '68197', '2.2538', '0', '1','2'),
(40123, '68198', '6.2601', '0', '1','2'),
(39436, '43624', '0.0064', '0', '1','1'),
(39436, '52363', '0.0043', '0', '1','1'),
(39436, '52364', '0.005', '0', '1','1'),
(39436, '52365', '0.005', '0', '1','1'),
(39436, '52366', '0.01', '0', '1','1'),
(39436, '52370', '0.0036', '0', '1','1'),
(39436, '52371', '0.0043', '0', '1','1'),
(39436, '52373', '0.0043', '0', '1','1'),
(39436, '52374', '0.0086', '0', '1','1'),
(39436, '52375', '0.0057', '0', '1','1'),
(39436, '52378', '0.0036', '0', '1','1'),
(39436, '52379', '0.02', '0', '1','1'),
(39436, '52382', '0.0071', '0', '1','1'),
(39436, '52385', '0.0057', '0', '1','1'),
(39436, '52386', '0.0036', '0', '1','1'),
(39436, '52494', '0.0043', '0', '1','1'),
(39436, '52495', '0.0036', '0', '1','1'),
(39436, '52568', '0.7567', '0', '3','3'),
(39436, '53010', '39.437', '0', '1','2'),
(39436, '55281', '0.0093', '0', '1','1'),
(39436, '55282', '0.015', '0', '1','1'),
(39436, '55283', '0.0164', '0', '1','1'),
(39436, '55290', '0.0164', '0', '1','1'),
(39436, '55291', '0.0114', '0', '1','1'),
(39436, '55292', '0.0157', '0', '1','1'),
(39436, '55299', '0.0043', '0', '1','1'),
(39436, '55301', '0.0107', '0', '1','1'),
(39436, '55308', '0.0235', '0', '1','1'),
(39436, '55309', '0.0243', '0', '1','1'),
(39436, '55310', '0.025', '0', '1','1'),
(39436, '55317', '0.0007', '0', '1','1'),
(39436, '55318', '0.0086', '0', '1','1'),
(39436, '55319', '0.0043', '0', '1','1'),
(39436, '55326', '0.0328', '0', '1','1'),
(39436, '55327', '0.03', '0', '1','1'),
(39436, '55328', '0.0385', '0', '1','1'),
(39436, '55335', '0.0136', '0', '1','1'),
(39436, '55336', '0.0128', '0', '1','1'),
(39436, '55337', '0.0136', '0', '1','1'),
(39436, '55344', '0.0178', '0', '1','1'),
(39436, '55345', '0.0164', '0', '1','1'),
(39436, '55346', '0.0207', '0', '1','1'),
(39436, '55353', '0.0043', '0', '1','1'),
(39436, '55362', '0.0435', '0', '1','1'),
(39436, '55363', '0.0399', '0', '1','1'),
(39436, '55364', '0.0314', '0', '1','1'),
(39436, '55371', '0.0264', '0', '1','1'),
(39436, '55372', '0.0264', '0', '1','1'),
(39436, '55373', '0.03', '0', '1','1'),
(39436, '55380', '0.0193', '0', '1','1'),
(39436, '55381', '0.025', '0', '1','1'),
(39436, '55382', '0.0214', '0', '1','1'),
(39436, '55389', '0.0171', '0', '1','1'),
(39436, '55390', '0.0121', '0', '1','1'),
(39436, '55391', '0.0121', '0', '1','1'),
(39436, '55398', '0.0621', '0', '1','1'),
(39436, '55399', '0.0991', '0', '1','1'),
(39436, '55400', '0.0542', '0', '1','1'),
(39436, '55407', '0.015', '0', '1','1'),
(39436, '55408', '0.0136', '0', '1','1'),
(39436, '55409', '0.0349', '0', '1','1'),
(39436, '55416', '0.0977', '0', '1','1'),
(39436, '55417', '0.1377', '0', '1','1'),
(39436, '55418', '0.1006', '0', '1','1'),
(39436, '55425', '0.0228', '0', '1','1'),
(39436, '55426', '0.0278', '0', '1','1'),
(39436, '55427', '0.0364', '0', '1','1'),
(39436, '55434', '0.0692', '0', '1','1'),
(39436, '55435', '0.1063', '0', '1','1'),
(39436, '55436', '0.0777', '0', '1','1'),
(39436, '55443', '0.0107', '0', '1','1'),
(39436, '55444', '0.0214', '0', '1','1'),
(39436, '55445', '0.0171', '0', '1','1'),
(39436, '55452', '0.0385', '0', '1','1'),
(39436, '55453', '0.0143', '0', '1','1'),
(39436, '55454', '0.0257', '0', '1','1'),
(39436, '55461', '0.0164', '0', '1','1'),
(39436, '55462', '0.0157', '0', '1','1'),
(39436, '55463', '0.01', '0', '1','1'),
(39436, '55479', '0.0499', '0', '1','1'),
(39436, '55480', '0.0578', '0', '1','1'),
(39436, '55481', '0.0571', '0', '1','1'),
(39436, '55488', '0.0278', '0', '1','1'),
(39436, '55489', '0.0385', '0', '1','1'),
(39436, '55490', '0.0428', '0', '1','1'),
(39436, '55497', '0.0428', '0', '1','1'),
(39436, '55498', '0.0385', '0', '1','1'),
(39436, '55499', '0.0357', '0', '1','1'),
(39436, '55506', '0.0392', '0', '1','1'),
(39436, '55507', '0.0442', '0', '1','1'),
(39436, '55508', '0.0314', '0', '1','1'),
(39436, '55515', '0.0342', '0', '1','1'),
(39436, '55516', '0.0292', '0', '1','1'),
(39436, '55517', '0.0364', '0', '1','1'),
(39436, '55524', '0.0428', '0', '1','1'),
(39436, '55525', '0.0571', '0', '1','1'),
(39436, '55526', '0.0606', '0', '1','1'),
(39436, '55533', '0.0506', '0', '1','1'),
(39436, '55534', '0.0321', '0', '1','1'),
(39436, '55535', '0.03', '0', '1','1'),
(39436, '55542', '0.0321', '0', '1','1'),
(39436, '55543', '0.0314', '0', '1','1'),
(39436, '55544', '0.0328', '0', '1','1'),
(39436, '55551', '0.0307', '0', '1','1'),
(39436, '55552', '0.0506', '0', '1','1'),
(39436, '55553', '0.0364', '0', '1','1'),
(39436, '55560', '0.0464', '0', '1','1'),
(39436, '55561', '0.0285', '0', '1','1'),
(39436, '55562', '0.0456', '0', '1','1'),
(39436, '55569', '0.0321', '0', '1','1'),
(39436, '55570', '0.03', '0', '1','1'),
(39436, '55571', '0.0328', '0', '1','1'),
(39436, '55578', '0.0257', '0', '1','1'),
(39436, '55579', '0.0378', '0', '1','1'),
(39436, '55580', '0.0428', '0', '1','1'),
(39436, '55587', '0.0407', '0', '1','1'),
(39436, '55588', '0.0399', '0', '1','1'),
(39436, '55589', '0.0428', '0', '1','1'),
(39436, '55596', '0.0449', '0', '1','1'),
(39436, '55597', '0.0635', '0', '1','1'),
(39436, '55598', '0.0414', '0', '1','1'),
(39436, '55605', '0.0514', '0', '1','1'),
(39436, '55606', '0.0314', '0', '1','1'),
(39436, '55607', '0.0235', '0', '1','1'),
(39436, '55614', '0.0314', '0', '1','1'),
(39436, '55615', '0.0357', '0', '1','1'),
(39436, '55616', '0.0307', '0', '1','1'),
(39436, '55623', '0.0435', '0', '1','1'),
(39436, '55624', '0.0449', '0', '1','1'),
(39436, '55625', '0.0399', '0', '1','1'),
(39436, '55632', '0.0407', '0', '1','1'),
(39436, '55633', '0.0635', '0', '1','1'),
(39436, '55634', '0.0342', '0', '1','1'),
(39436, '55641', '0.03', '0', '1','1'),
(39436, '55642', '0.0521', '0', '1','1'),
(39436, '55643', '0.0378', '0', '1','1'),
(39436, '55650', '0.0371', '0', '1','1'),
(39436, '55651', '0.0442', '0', '1','1'),
(39436, '55652', '0.0435', '0', '1','1'),
(39436, '55659', '0.0414', '0', '1','1'),
(39436, '55660', '0.0435', '0', '1','1'),
(39436, '55661', '0.0335', '0', '1','1'),
(39436, '55668', '0.0478', '0', '1','1'),
(39436, '55669', '0.0514', '0', '1','1'),
(39436, '55670', '0.0292', '0', '1','1'),
(39436, '55677', '0.0442', '0', '1','1'),
(39436, '55678', '0.0435', '0', '1','1'),
(39436, '55679', '0.0371', '0', '1','1'),
(39436, '55686', '0.0349', '0', '1','1'),
(39436, '55687', '0.0335', '0', '1','1'),
(39436, '55688', '0.03', '0', '1','1'),
(39436, '55695', '0.0335', '0', '1','1'),
(39436, '55696', '0.0364', '0', '1','1'),
(39436, '55697', '0.0285', '0', '1','1'),
(39436, '55704', '0.0642', '0', '1','1'),
(39436, '55705', '0.0563', '0', '1','1'),
(39436, '55706', '0.0542', '0', '1','1'),
(39436, '55713', '0.0585', '0', '1','1'),
(39436, '55714', '0.0592', '0', '1','1'),
(39436, '55715', '0.0485', '0', '1','1'),
(39436, '55722', '0.0407', '0', '1','1'),
(39436, '55723', '0.0827', '0', '1','1'),
(39436, '55724', '0.0735', '0', '1','1'),
(39436, '55731', '0.0756', '0', '1','1'),
(39436, '55732', '0.0792', '0', '1','1'),
(39436, '55733', '0.0635', '0', '1','1'),
(39436, '55740', '0.0471', '0', '1','1'),
(39436, '55741', '0.0485', '0', '1','1'),
(39436, '55742', '0.0514', '0', '1','1'),
(39436, '55749', '0.0785', '0', '1','1'),
(39436, '55750', '0.0535', '0', '1','1'),
(39436, '55751', '0.0649', '0', '1','1'),
(39436, '55758', '0.0506', '0', '1','1'),
(39436, '55759', '0.0649', '0', '1','1'),
(39436, '55760', '0.0571', '0', '1','1'),
(39436, '55767', '0.1191', '0', '1','1'),
(39436, '55768', '0.0506', '0', '1','1'),
(39436, '55769', '0.0799', '0', '1','1'),
(39436, '58256', '7.0596', '0', '1','1'),
(39436, '58268', '14.239', '0', '1','1'),
(39436, '62063', '0.1355', '0', '1','1'),
(39436, '62064', '0.1619', '0', '1','1'),
(39436, '62065', '0.1733', '0', '1','1'),
(39436, '62066', '0.1833', '0', '1','1'),
(39436, '62067', '0.1769', '0', '1','1'),
(39436, '62068', '0.1726', '0', '1','1'),
(39436, '62069', '0.1633', '0', '1','1'),
(39436, '62070', '0.1619', '0', '1','1'),
(39436, '62071', '0.2254', '0', '1','1'),
(39436, '62072', '0.1377', '0', '1','1'),
(39436, '62073', '0.2289', '0', '1','1'),
(39436, '62074', '0.2168', '0', '1','1'),
(39436, '62075', '0.174', '0', '1','1'),
(39436, '62076', '0.2767', '0', '1','1'),
(39436, '62077', '0.2011', '0', '1','1'),
(39436, '62078', '0.2083', '0', '1','1'),
(39436, '62079', '0.2175', '0', '1','1'),
(39436, '62080', '0.2275', '0', '1','1'),
(39436, '62081', '0.2361', '0', '1','1'),
(39436, '62082', '0.2068', '0', '1','1'),
(39436, '62083', '0.2675', '0', '1','1'),
(39436, '62084', '0.2846', '0', '1','1'),
(39436, '62085', '0.2125', '0', '1','1'),
(39436, '62086', '0.2268', '0', '1','1'),
(39436, '62087', '0.2767', '0', '1','1'),
(39436, '62088', '0.2375', '0', '1','1'),
(39436, '62089', '0.2375', '0', '1','1'),
(39436, '62090', '0.1947', '0', '1','1'),
(39436, '62091', '0.199', '0', '1','1'),
(39436, '62092', '0.2175', '0', '1','1'),
(39436, '62093', '0.209', '0', '1','1'),
(39436, '62094', '0.204', '0', '1','1'),
(39436, '62095', '0.1904', '0', '1','1'),
(39436, '62096', '0.2568', '0', '1','1'),
(39436, '62097', '0.2382', '0', '1','1'),
(39436, '62098', '0.2389', '0', '1','1'),
(39436, '62099', '0.219', '0', '1','1'),
(39436, '62100', '0.1819', '0', '1','1'),
(39436, '62101', '0.2596', '0', '1','1'),
(39436, '62102', '0.2532', '0', '1','1'),
(39436, '62103', '0.199', '0', '1','1'),
(39436, '62104', '0.2061', '0', '1','1'),
(39436, '66895', '0.0043', '0', '1','1'),
(39436, '66958', '0.0043', '0', '1','1'),
(39436, '66980', '0.005', '0', '1','1'),
(39436, '67027', '0.0036', '0', '1','1'),
(39436, '67029', '0.0043', '0', '1','1'),
(39436, '67099', '0.0071', '0', '1','1'),
(39436, '67104', '0.0036', '0', '1','1'),
(39436, '67105', '0.0036', '0', '1','1'),
(39436, '67109', '0.0093', '0', '1','1'),
(39436, '67539', '0.4586', '0', '1','1'),
(39436, '68197', '5.5632', '0', '1','2'),
(39436, '68198', '16.2325', '0', '1','2'),
(39436, '68783', '0.0071', '0', '1','1'),
(39436, '68789', '0.0043', '0', '1','1');

INSERT INTO `creature_loot_template` (`entry`,`Item`,`Chance`,`QuestRequired`,`GroupId`,`MinCount`,`MaxCount`) values
(40123, '53139', '85.6002', '1', '0', '1','1');