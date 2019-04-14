=========================================================
diskpart
list disk
select disk []
clean
create partition primary
format fs=ntfs quick
assign
active
exit

dism /apply-image /imagefile:install.wim /index:1 /applydir:E:\

=========================================================
我们不能够直接从安装镜像中提取install.wim文件。
通常我们从官网下载Windows 10 的镜像都是ISO 格式的。 我们右击该文件mount之后能够在source文件夹下找到install.esd文件。然后使用DISM命令行工具将install.esd文件中的install.wim文件提取出来。具体做法如下：
1.在C 盘（系统盘）下，创建一个新的文件夹命名为esd, 将install.esd文件放在该文件夹下。
2.使用管理员身份打开命令行工具。
3.运行命令：cd c:\esd 
4.运行命令以显示esd文件中的内容：dism /Get-WimInfo /WimFile:install.esd
5.找到你想要导出的文件内容序号，比如index:1，然后运行命令进行提取:
dism /export-image /SourceImageFile:install.esd /SourceIndex:1 /DestinationImageFile:install.wim /Compress:max /CheckIntegrity
6.在文件夹c:\esd中你将会发现新生成的一个文件install.wim
=========================================================