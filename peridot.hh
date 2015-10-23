<?hh //partial

use Evenement\EventEmitterInterface;
use Peridot\Reporter\Dot\DotReporterPlugin;
use expect\peridot\ExpectPlugin;

return function(EventEmitterInterface $emitter) {
    ExpectPlugin::create()->registerTo($emitter);
    (new DotReporterPlugin($emitter));
};
