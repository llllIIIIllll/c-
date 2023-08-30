docker inspect --format='{{.State.Running}}' 

docker inspect --format='{{.Config.Labels}}{{build_version}}' d0f33262444d5c00b112ad3b9d954b845dcecd765cd4a17c8dd8678fdac11c8e

docker inspect --format='{{.Config.Labels."com.docker.compose.project.working_dir"}}' d0f33262444d5c00b112ad3b9d954b845dcecd765cd4a17c8dd8678fdac11c8e docker network inspect --format='{{/*查看容器的默认网关*/}}{{range .IPAM.Config}}{{.Gateway}}{{end}}' bridge 


docker network inspect --format='{{range .IPAM.Config}}{{.Gateway}}{{end}}' bridge 

docker inspect --format='{{(index .Config.Labels 0).com.docker.compose.project.working_dir}}' d0f33262444d5c00b112ad3b9d954b845dcecd765cd4a17c8dd8678fdac11c8e

docker container ls -q |xargs docker inspect --format='{{(index .Config.Labels "com.docker.compose.project.working_dir")}}'

docker container ls -q |xargs docker inspect --format='{{.Config.Labels}}'

docker container ls -q |xargs docker inspect --format='{{(index .Config.Labels "com.docker.compose.project.working_dir")}}'
docker container ls -q |xargs docker inspect --format='{{(index .Config.Labels "com.docker.compose.project.working_dir")}}/{{(index .Config.Labels "com.docker.compose.project.working_dir")}}'

docker container ls -q |xargs docker inspect --format='{{(index .Config.Labels "com.docker.compose.project.working_dir")}}/{{(index .Config.Labels "com.docker.compose.project.config_files")}}'

docker container ls -q |xargs docker inspect --format='{{(index .Config.Labels "com.docker.compose.project.working_dir")}}/{{(index .Config.Labels "com.docker.compose.project.config_files")}}'
