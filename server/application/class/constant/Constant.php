<?php

/**
 * Created by PhpStorm.
 * File: Constant.php.
 * Created: bigtows.
 * Created date: 29/05/2017  20:25
 * Description:
 */
class Constant
{
    /**
     * Types
     */
    const USER_TYPE = 1;
    const DOCTOR_TYPE = 2;
    /**
     * DataBase
     */
      const DATABASE_NAME = "Hospital";
      const DOCTOR_TABLE = "doctor";
      const USER_TABLE = "user";
      const SESSION_DOCTOR_TABLE = "session_auth_doctor";
      const SESSION_USER_TABLE = "session_auth_user";
}