<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\process\stream;

use hhpack\process\OutputResult;

interface StreamManager
{
    /**
     * Reads the data from the STDOUT/STDERR
     */
    public function read() : void;

    /**
     * Write the data into STDIN
     */
    public function write() : void;

    /**
     * Close all the stream
     */
    public function close() : void;

    /**
     * Return the result of stream
     */
    public function getOutputResult() : OutputResult;
}
