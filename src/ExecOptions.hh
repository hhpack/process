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

use HHPack\Process\Input\{ReadableStream, NullInputStream};

final class ExecOptions implements Options {

  private ReadableStream<int> $input;

  public function __construct(
    private string $cwd = (string) getcwd(),
    private ?environment $env = null,
  ) {
    $this->input = new NullInputStream();
  }

  public function workingDirectory(string $cwd): this {
    $this->cwd = $cwd;
    return $this;
  }

  public function environment(?environment $environment = null): this {
    $this->env = $environment;
    return $this;
  }

  public function stdin(ReadableStream<int> $input): this {
    $this->input = $input;
    return $this;
  }

  public function applyTo(ProcessBuilder $bulider): void {
    $bulider->environment($this->env);
    $bulider->workingDirectory($this->cwd);
    $bulider->stdin($this->input);
  }

}
