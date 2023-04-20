
### pacemarker configuare

1. The capacity a certain node provides.
2. The capacity a certain resource requires.
3. An overall strategy for placement of resources.




### Resource constrains
Any value + INFINITY = INFINITY
Any value - INFINITY = -INFINITY
INFINITY - INFINITY = -INFINITY

# 1. 非对称cluster: Opt-In

只允许resource运行在特定node
```
crm_attribute --name symmetric-cluster --update false

sudo crm configure location WL-gw-srv-01-do-not-run wg 200: "WL-gw-srv-01"
```


# 2. 对称cluster: Opt-out

设置成  -INFINITY 使得resource不运行在某一节点上
```
crm_attribute --name symmetric-cluster --update true

sudo crm configure location WL-gw-srv-01-do-not-run wg -INFINITY: "WL-gw-srv-01"
```

Plain resource reference: location loc1 webserver 100: node1
Resource set in curly brackets: location loc1 { virtual-ip webserver } 100: node1
Tag containing resource ids: location loc1 tag1 100: node1
Resource pattern: location loc1 /web.*/ 100: node1



# 3. 顺序启动 resource

kind="Mandatory/Optional/Serialize"
当前版本不支持
```
sudo crm configure order id=od-1 wg test
```


# 4. resource 与 resource 绑定节点

g_test g_wg 运行在同一节点
如下 g_test 能启动在任意节点 但g_wg 只能在g_test成功启动的节点上启动
```
sudo crm configure colocation id="colocate" INFINITY: g_wg g_test
```

g_test g_wg 运行在不同节点
```
sudo crm configure colocation id="anti-colocate" -INFINITY: g_wg g_test
```

非绝对限制
```
sudo crm configure colocation id="anti-colocate" 500: g_wg g_test
```


# 5. resource set

```xml
<constraints>
    <rsc_order id="order-1">
      <resource_set id="ordered-set-1" sequential="false">
        <resource_ref id="A"/>
        <resource_ref id="B"/>
      </resource_set>
      <resource_set id="ordered-set-2" sequential="true">
        <resource_ref id="C"/>
        <resource_ref id="D"/>
      </resource_set>
      <resource_set id="ordered-set-3" sequential="false">
        <resource_ref id="E"/>
        <resource_ref id="F"/>
      </resource_set>
    </rsc_order>
</constraints>
```
A                     E
    -->  C  --> D -->
B                     F

