var zoom = 0.1;

var max = 0;
for (var i = 0; i < data.length; ++i) {
  var cmd = data[i];
  if (cmd.end > max)
    max = cmd.end;
}

for (var i = 0; i < (max + 500); i += 1000) {
  var line = document.createElement('div');
  line.className = 'line';
  line.style.left = (i * zoom) + 'px';
  document.body.appendChild(line);
}

for (var i = 0; i < data.length; ++i) {
  var cmd = data[i];
  var div = document.createElement('div');
  div.className = 'cmd';
  div.style.left = (cmd.start * zoom) + 'px';

  div.innerText = cmd.target;

  var bar = document.createElement('div');
  bar.className = 'bar';
  bar.style.width = ((cmd.end - cmd.start) * zoom) + 'px';
  div.appendChild(bar);

  document.body.appendChild(div);

  if (cmd.end > max)
    max = cmd.end;
}
