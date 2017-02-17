<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Process\Stream;

use HHPack\Process\OutputResult;

interface StreamManager
{
    /**
     * Reads the data from the STDOUT/STDERR
     */
    public function read() : Awaitable<void>;

    /**
     * Write the data into STDIN
     */
    public function write() : Awaitable<void>;

    /**
     * Close all the stream
     */
    public function close() : void;

    /**
     * Return the result of stream
     */
    public function getOutputResult() : OutputResult;
}
