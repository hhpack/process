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

final class OutputResult
{

    public function __construct(
        private BufferedOutput $stdout,
        private BufferedOutput $stderr
    )
    {
    }

    public static function fromOutputs(Outputs $outputs) : OutputResult
    {
        return new OutputResult(
            $outputs['stdout'],
            $outputs['stderr']
        );
    }

    public static function emptyResult() : OutputResult
    {
        return new OutputResult(
            new BufferedOutput(),
            new BufferedOutput()
        );
    }

}
