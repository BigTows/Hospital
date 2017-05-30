<?php

/**
 * Created by PhpStorm.
 * File: User.php.
 * Created: bigtows.
 * Created date: 27/05/2017  00:08
 * Description:
 */

/**
 * Interface Entity
 */
interface Entity
{
    /**
     * Entity constructor.
     * @param $token
     */
    public function __construct($token);

    /**
     * @return bool
     */
    public function isAuth():bool;

    /**
     * @return array
     */
    public function getName():array;

    /**
     * @return string
     */
    public function getFirstName():string;

    /**
     * @return string
     */
    public function getSecondName():string;

    /**
     * @return string
     */
    public function getPhoto():string;

    /**
     * @return string
     */
    public function getEmail():string;

    /**
     * @return string
     */
    public function getNumberPolis():string;
}