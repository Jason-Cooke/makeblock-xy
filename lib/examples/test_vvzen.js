const plotter = require('./../index.js')();
var job = plotter.Job('test-job');

console.log("Starting new job");
//job.rect(10, 10, 100, 100).circle(10, 10, 100);
job.pen_down().move(100, 100);

var serial = plotter.Serial('/dev/tty.Repleo-CH341-000013FA');

serial.send(job).then(() => {
    console.log('the job is done !');
});