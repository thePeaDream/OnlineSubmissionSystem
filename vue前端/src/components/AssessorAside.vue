<template>
  <el-menu
    default-active="1"
    class="el-menu-vertical-demo"
    background-color="#545c64"
    text-color="#fff"
    active-text-color="#ffd04b"
    style="width:200px;min-height: 100vh;position:fixed"
  >
    <h3>在线投稿系统</h3>
    <el-menu-item index="1" @click="clickMenu('/personalCenter')">
      <i class="el-icon-menu"></i>
      <span slot="title">个人中心</span>
    </el-menu-item>

    <el-menu-item index="2" @click="clickMenu('/manuscriptAudit')">
      <i class="el-icon-location"></i>
      <span slot="title">稿件审核</span>
    </el-menu-item>

    <el-menu-item index="3" @click="clickMenu('/historyNotice')">
      <i class="el-icon-document"></i>
      <span slot="title">历史通知</span>
    </el-menu-item>

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
        role:2
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

