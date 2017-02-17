<?hh // strict

/**
 * This file is part of hhpack\process package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Process;

use HHPack\Process\Writable;
use HHPack\Process\Stream\StreamType;
use HHPack\Process\Descriptor\ReadDescriptor;
use HHPack\Process\Descriptor\WriteDescriptor;
use HHPack\Process\Descriptor\DescriptorRegistry;
use HHPack\Process\Descriptor\DefaultDescriptorRegistry;
use HHPack\Process\Descriptor\DescriptorSpecification;
use HHPack\Process\Input\ReadableStream;
use HHPack\Process\Input\NullInputStream;
use HHPack\Process\Output\BufferedOutputStream;
use RuntimeException;

final class ProcessBuilder
{

    private string $cwd;
    private Mode $mode;
    private ?environment $env;
    private ReadableStream<int> $input;
    private Output $output;
    private Output $errorOutput;

    public function __construct(
        private string $command,
        Options $options = new ProcessOptions()
    )
    {
        $this->cwd = (string) getcwd();
        $this->mode = Mode::Normal;
        $this->env = null;
        $this->input = new NullInputStream();
        $this->output = new BufferedOutputStream();
        $this->errorOutput = new BufferedOutputStream();
        $options->applyTo($this);
    }

    public function mode(Mode $mode) : this
    {
        $this->mode = $mode;
        return $this;
    }

    public function command(string $command) : this
    {
        $this->command = $command;
        return $this;
    }

    public function workingDirectory(string $cwd) : this
    {
        $this->cwd = $cwd;
        return $this;
    }

    public function environment(?environment $environment = null) : this
    {
        $this->env = $environment;
        return $this;
    }

    public function stdin(ReadableStream<int> $input) : this
    {
        $this->input = $input;
        return $this;
    }

    public function stdout(Output $output) : this
    {
        $this->output = $output;
        return $this;
    }

    public function stderr(Output $output) : this
    {
        $this->errorOutput = $output;
        return $this;
    }

    public function start() : ChildProcess
    {
        $streamHandles = [];
        $descriptors = $this->createDescriptors();

        $process = proc_open(
            $this->command,
            $descriptors->toArray(),
            $streamHandles,
            $this->cwd,
            $this->env
        );

        if (is_resource($process) === false) {
            throw new RuntimeException('Failed to start of process');
        }

        $streamManager = $descriptors->createStreamManager($streamHandles);

        return new ChildProcess($process, $streamManager);
    }

    private function createDescriptors() : DescriptorRegistry
    {
        return new DefaultDescriptorRegistry(
            new WriteDescriptor(StreamType::Stdin, [ 'pipe', 'r' ], $this->input),
            new ReadDescriptor(StreamType::Stdout, [ 'pipe', 'w' ], $this->output),
            new ReadDescriptor(StreamType::Stderr, [ 'pipe', 'w' ], $this->errorOutput)
        );
    }

}
