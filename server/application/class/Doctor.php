<?php

/**
 * Created by PhpStorm.
 * File: Doctor.php.
 * Created: bigtows.
 * Created date: 27/05/2017  00:39
 * Description:
 */
class Doctor extends User {

    /**
     * Doctor constructor.
     * @param $sessionID
     */
    public function __construct($sessionID)
    {
        parent::__construct($sessionID);
    }
    
}