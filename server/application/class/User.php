<?php

/**
 * Created by PhpStorm.
 * File: User.php.
 * Created: bigtows.
 * Created date: 27/05/2017  00:12
 * Description:
 */
class User implements Entity
{
    private $sessionID;

    /**
     * User constructor.
     * @param $sessionID
     */
    public function __construct($sessionID)
    {
        $this->sessionID=$sessionID;
    }

    /**
     * @return bool
     */
    public function isAuth(): bool
    {
        // TODO: Implement isAuth() method.
    }

    /**
     * @return array
     */
    public function getName(): array
    {
        // TODO: Implement getName() method.
    }

    /**
     * @return string
     */
    public function getFirstName(): string
    {
        // TODO: Implement getFirstName() method.
    }

    /**
     * @return string
     */
    public function getSecondName(): string
    {
        // TODO: Implement getSecondName() method.
    }

    /**
     * @return string
     */
    public function getPhoto(): string
    {
        // TODO: Implement getPhoto() method.
    }

    /**
     * @return string
     */
    public function getEmail(): string
    {
        // TODO: Implement getEmail() method.
    }

    /**
     * @return string
     */
    public function getNumberPolis(): string
    {
        // TODO: Implement getNumberPolis() method.
    }
}