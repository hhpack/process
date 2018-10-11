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
use HHPack\Process\Input\{ReadableStream, NullInputStream};
use HHPack\Process\Output\BufferedOutputStream;

final class ProcessOptions implements Options {

  private ReadableStream $input;
  private Output $output;
  private Output $errorOutput;

  public function __construct(
    private string $cwd = (string)\getcwd(),
    private ?environment $env = null,
  ) {
    $this->cwd = (string)\getcwd();
    $this->input = new NullInputStream();
    $this->output = new BufferedOutputStream();
    $this->errorOutput = new BufferedOutputStream();
  }

  public function workingDirectory(string $cwd): this {
    $this->cwd = $cwd;
    return $this;
  }

  public function environment(?environment $environment = null): this {
    $this->env = $environment;
    return $this;
  }

  public function stdin(ReadableStream $input): this {
    $this->input = $input;
    return $this;
  }

  public function stdout(Output $output): this {
    $this->output = $output;
    return $this;
  }

  public function stderr(Output $output): this {
    $this->errorOutput = $output;
    return $this;
  }

  public function applyTo(ProcessBuilder $bulider): void {
    $bulider->environment($this->env);
    $bulider->workingDirectory($this->cwd);
    $bulider->stdin($this->input);
    $bulider->stdout($this->output);
    $bulider->stderr($this->errorOutput);
  }

}
