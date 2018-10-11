<?hh //strict

namespace HHPack\Process\Test;

use HHPack\Process\Stream\StreamType;
use HHPack\Process\Descriptor\WriteDescriptor;
use LogicException;
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class WriteDescriptorTest extends HackTest {
  public function testUnsupportType(): void {
    expect(() ==> {
      $descriptor = new WriteDescriptor(StreamType::Stdout, ['pipe', 'r']);
    })->toThrow(LogicException::class);
  }
}
