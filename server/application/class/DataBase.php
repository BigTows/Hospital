<?php

/**
 * Created by PhpStorm.
 * File: DataBase.php.
 * Created: bigtows.
 * Created date: 26/05/2017  23:46
 * Description:
 */

/**
 * Class DataBase
 */
class DataBase
{
    /**
     * @var PDO
     */
    private $DBConnect;
    /**
     * @var bool
     */
    private $debug = true;
    /**
     * @var bool
     */
    private $hasError = false;

    /**
     * DataBase constructor.
     * @param $dns
     * @param $user
     * @param string $password
     */
    function __construct($dns, $user, $password = "")
    {
        try {
            $this->DBConnect = new PDO($dns, $user, $password);
        } catch (PDOException $exception) {
            $this->log($exception);
        }
    }

    /**
     * @param $SQL
     * @param array $Array
     * @param int $type
     * @return PDOStatement
     */
    public function sendQuery($SQL, $Array = [], $type = PDO::PARAM_STR)
    {
        $statement = $this->DBConnect->prepare($SQL);
        foreach ($Array as $key => $item) {
            $statement->bindValue(":" . $key, $item, $type);
            $this->log("Bind :" . $key . " " . $item . "<br>");
        }
        $statement->execute();
        if ($statement->errorCode() == 0) {
            $this->hasError = false;
        } else {
            $this->hasError = true;
        }
        return $statement;
    }

    /**
     *
     */
    public function test()
    {
        echo "yeap";
    }

    /**
     * @return bool
     */
    public function hasError()
    {
        return $this->hasError;
    }

    /**
     * @param $status
     */
    public function setDebug($status)
    {
        $this->debug = $status;
    }

    /**
     * @param $message
     */
    private function log($message)
    {
        if (false && $this->debug) echo "Class DataBase -> " . $message;
    }
}