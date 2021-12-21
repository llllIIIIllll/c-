#!/bin/bash

mkdir -p /opt/qomolo || true

echo """
#!/bin/bash
/home/westwell/Documents/well_driver/script/start_docker_local.sh
/home/westwell/Documents/well_driver/script/start_server_monitor.sh
""" | sudo tee /opt/qomolo/qtruck_gcs_startup.sh 

sudo chmod +x /opt/qomolo/qtruck_gcs_startup.sh

echo """
[Unit]
Description=qtruck startup

[Service]
Type=simple
User=westwell
Environment=DISPLAY=:0
ExecStart=/bin/bash /opt/qomolo/qtruck_gcs_startup.sh

[Install]
After=default.target
""" | sudo tee /lib/systemd/system/qtruck_gcs_startup.service

sudo systemctl daemon-reload
sudo systemctl enable qtruck_gcs_startup.service
