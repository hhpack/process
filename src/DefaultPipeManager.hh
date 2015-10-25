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

final class DefaultPipeManager implements PipeManager
{

    public function __construct(
        private PipeRegistry $pipes
    )
    {
    }

    public function read() : void
    {
        $this->pipes->read();
    }

    public function close() : void
    {
        $this->pipes->close();
    }

    public function getOutputResult() : OutputResult
    {
        return $this->pipes->getOutputResult();
    }

}
