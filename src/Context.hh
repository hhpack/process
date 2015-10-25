<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\process;

interface Context
{
    public function getPid() : ?int;
    public function getCommand() : string;
    public function getWorkingDirectory() : string;
    public function getEnvironmentVariables() : EnviromentVariables; // XXX value is string?
    public function start() : void;
    public function stop() : ProcessResult;
    public function wait() : Awaitable<ProcessResult>;
    public function run() : Awaitable<ProcessResult>;
    public function isAlive() : bool;
}
