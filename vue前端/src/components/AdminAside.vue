<template>
  <el-menu
    default-active="1"
    class="el-menu-vertical-demo"
    background-color="#545c64"
    text-color="#fff"
    active-text-color="#ffd04b"
    style="width:200px;min-height:100vh; position:fixed"
  >
    <h3>在线投稿系统</h3>
    <el-menu-item index="1" @click="clickMenu('/personalCenter')">
      <i class="el-icon-menu"></i>
      <span slot="title">个人中心</span>
    </el-menu-item>

    <el-menu-item index="2" @click="clickMenu('/logManage')">
      <i class="el-icon-location"></i>
      <span slot="title">系统日志管理</span>
    </el-menu-item>

    <el-menu-item index="3" @click="clickMenu('/manuscriptManage')">
      <i class="el-icon-location"></i>
      <span slot="title">稿件管理</span>
    </el-menu-item>

    <el-menu-item index="4" @click="clickMenu('/categoryManage')">
      <i class="el-icon-location"></i>
      <span slot="title">稿件类型管理</span>
    </el-menu-item>

    <el-submenu index="5">
      <span slot="title">用户管理</span>
        <el-menu-item index="5-1" @click="clickMenu('/writerManage')">作者管理</el-menu-item>
        <el-menu-item index="5-2" @click="clickMenu('/assessorManage')">审核员管理</el-menu-item>
        <el-menu-item index="5-3" @click="clickMenu('/assessorApplicationManage')">审核员申请管理</el-menu-item>
    </el-submenu>

    <el-submenu index="6">
      <span slot="title">通知管理</span>
        <el-menu-item index="6-1" @click="clickMenu('/historyNotice')">历史通知</el-menu-item>
        <el-menu-item index="6-2" @click="clickMenu('/publishNotice')">发布通知</el-menu-item>
    </el-submenu>

  </el-menu>
</template>

<script>
export default {
  methods: {
    clickMenu(item) {
      //当前路径和目标路径不一样，才跳转
      if (this.$route.path !== item) this.$router.push(item);
    },
  },
  data() {
    return {
        role:3
    };
  },
};
</script>

<style scoped>
h3 {
  text-align: center;
  line-height: 48px;
  color: #fff;
  font-weight: 400;
  font-size: 16px;
}
</style>
