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
use HHPack\Process\Output\{NullOutputStream, OutputBufferedStream};

final class OutputResult implements Displayable {

  public function __construct(private Output $stdout, private Output $stderr) {}

  public function stdout(): Output {
    return $this->stdout;
  }

  public function stderr(): Output {
    return $this->stderr;
  }

  public static function fromOutputs(Outputs $outputs): this {
    return new static($outputs['stdout'], $outputs['stderr']);
  }

  public static function emptyResult(): this {
    return new static(new NullOutputStream(), new NullOutputStream());
  }

  public function display(): void {
    $this->displayOutput('stdout: ', $this->stdout);
    $this->displayOutput('stderr: ', $this->stderr);
  }

  private function displayOutput(string $header, Output $output): void {
    if (!($output instanceof Displayable)) {
      return;
    }
    fwrite(STDOUT, $header);
    $output->display();
  }

}
