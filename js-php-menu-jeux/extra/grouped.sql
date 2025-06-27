-- phpMyAdmin SQL Dump
-- version 4.7.0
-- https://www.phpmyadmin.net/
--
-- Hôte : 127.0.0.1
-- Généré le :  mar. 07 mai 2024 à 21:55
-- Version du serveur :  5.7.17
-- Version de PHP :  5.6.30

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données :  `grouped`
--

-- --------------------------------------------------------

--
-- Structure de la table `4img1mot_progress`
--

CREATE TABLE `4img1mot_progress` (
  `progress_id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `theme` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `points` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Déchargement des données de la table `4img1mot_progress`
--

INSERT INTO `4img1mot_progress` (`progress_id`, `user_id`, `theme`, `points`) VALUES
(1, 1, 'pays', 100),
(2, 1, 'astronomie', 75),
(3, 2, 'pays', 150),
(4, 2, 'astronomie', 200),
(5, 25, 'astronomie', 520),
(6, 25, 'films', 620),
(7, 22, 'pays', 250);

-- --------------------------------------------------------

--
-- Structure de la table `users`
--

CREATE TABLE `users` (
  `iduser` int(11) NOT NULL,
  `login` varchar(30) COLLATE utf8_unicode_ci NOT NULL,
  `password` varchar(255) COLLATE utf8_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Déchargement des données de la table `users`
--

INSERT INTO `users` (`iduser`, `login`, `password`) VALUES
(22, 'azerty1000_', '$2y$10$X/dW4QD4ptvZbFZpBRbxbeojw/Dw79RB5gVA0llv.q5JBnp9hE8Em'),
(23, 'norabni123_', '$2y$10$csmoWy5qeoi9wECmcKbLTuqvFU07Gc0CoHBybHU50tUxsu2H.CBvK'),
(24, 'nouveau123_', '$2y$10$egf5UNB3uxxp8fzwndyJveF0Q9Jkt3kkgIooXT0cTMmHgdu2m8kF2'),
(25, 'lamyae1_', '$2y$10$2qVD7RNt8ncVQ3qwONRGkeVphHcGQetQqDRL1NXWEV4o6v.LJuRUO'),
(26, 'NoraBni90_', '$2y$10$P8a8NHVURkaVHE6ThjuhBunY1g67XqTNpvjiiAwIjCQXdN2Pj0Bke'),
(32, 'AZRReer90_', '$2y$10$xw6OudLl6GU7D2ytxxgPk.WJID41ocWczqxrg7tBcJ0ntDdWwxiAy'),
(33, 'LAMAlg00_', '$2y$10$KHFMlhpIROJ.lHYitwD2gOBzYYJ6mkT9UxeqVwPZptubWXqJ5X5Gu'),
(34, 'NORAazDSD0_', '$2y$10$5YRaV7Y1GZ.yMYfH.oVF9OdhDL8kenOUJTJLLgn5mfTDmHeXax.9q'),
(35, 'sfqsfqs0980_', '$2y$10$UTptSUosNHS6SU4RbPBxcet09DnxBazLe6/JQhwkndlJJHqZ/RbU.'),
(36, 'sdFfq353_', '$2y$10$N/Xf3VFYJBOHwfMtX/dUPe/MVUPL4T5YCM3NQpFlzM4Wt//79cpzC'),
(37, 'QDFFDSqsdf80_', '$2y$10$bqKWVwA6eLdRQz41FMJtpeHqJiNBzwebV5/TBIfeXd3Db4hFkWNS2'),
(38, 'sqfqsdfFSFD80_', '$2y$10$q3XxpxXtb/PkRIAc8UZzwuds9ZGjBwgLN6qEeyh43hmH/8ZwmXnpC'),
(39, 'Lamrz08098_', '$2y$10$svZZD0cKIqhXx/bustyivOfjfJlW0NP10UIIHKed3FhL/0D5BbFZu'),
(40, 'NVtesssssss09_', '$2y$10$5Ym3Z9KvjyMAvA5.YJnWLOSkYJj.X/mKCeBNDHUXe55d03d9Z2pZO'),
(41, 'loginA123_', '$2y$10$zxnDr4WOJyFKMhJCLbOlNudJ1fg3uUzwi0x4UCr/xfTE2laGzGlmK'),
(42, 'SDFQFgdqdg424-', '$2y$10$68sI5US2oweEx.in9jgaZOzEkfQKtZ6TBiIQMbKizAJkaPokvphYa'),
(43, 'qgdfdqgd234_', '$2y$10$O0YdwpEg36AKFNLuG6Z6GevWbPu0QxEsxt.ZSsDzUmA8blMaaVTsG'),
(44, 'aqwXSZ098_', '$2y$10$iWNW5BeZ3LhdEmbDuEu96unXH.f4ESj5i/iujH86lAP.QWm2n/w.G'),
(46, 'qfsERZE9080_', '$2y$10$U92JBzs1pCzghiBUQfT.quzZmv45n98A36NHAPT6zQ0W1iueRjEgS'),
(47, 'QSqsfqsdfq980_', '$2y$10$MvtVdGQeo1Vo0eLFqffmGeMu85zDRsixR1/OsDaudES7KTF9jqcT.'),
(48, 'SDFSfsfsq89_', '$2y$10$GngQci4lzEubSD0wpIjJVeV97SRdmxh1wOGRF9Kb897QPTAKWJUme'),
(49, 'loginMot123_4', '$2y$10$QMn0rrXrVq/foRD80JAZEerygNneCxduvVQAo05OdKZbRnQ0mY14G');

-- --------------------------------------------------------

--
-- Structure de la table `wordle_progress`
--

CREATE TABLE `wordle_progress` (
  `user_id` int(11) NOT NULL,
  `level` int(11) NOT NULL DEFAULT '0',
  `points` int(11) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Déchargement des données de la table `wordle_progress`
--

INSERT INTO `wordle_progress` (`user_id`, `level`, `points`) VALUES
(22, 46, 356),
(23, 7, 68),
(24, 1, 10),
(33, 2, 20),
(44, 3, 29),
(39, 1, 10);

--
-- Index pour les tables déchargées
--

--
-- Index pour la table `4img1mot_progress`
--
ALTER TABLE `4img1mot_progress`
  ADD PRIMARY KEY (`progress_id`),
  ADD UNIQUE KEY `user_id_theme_unique` (`user_id`,`theme`);

--
-- Index pour la table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`iduser`),
  ADD UNIQUE KEY `UniqueLogin` (`login`);

--
-- Index pour la table `wordle_progress`
--
ALTER TABLE `wordle_progress`
  ADD PRIMARY KEY (`user_id`);

--
-- AUTO_INCREMENT pour les tables déchargées
--

--
-- AUTO_INCREMENT pour la table `4img1mot_progress`
--
ALTER TABLE `4img1mot_progress`
  MODIFY `progress_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;
--
-- AUTO_INCREMENT pour la table `users`
--
ALTER TABLE `users`
  MODIFY `iduser` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=50;COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
