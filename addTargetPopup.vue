<template>
    <div class="popup-background">
        
        <div class="frame popup-frame">
            <button class="close-btn" @click="closeAddTarget()">X</button>
            <div class="list-box" id="add-trans-box">
                전환
                <button style="height:4vh; width:4vh; float:right; background:none; border:none; font-size:3rem; color:#3DC984" >+</button>
                <div class="list-content-group">
                    <div class="list-content" v-for = "trans in transList" v-on:mouseover="hoverTarget(trans)" v-on:mouseleave="leaveTarget()">
                        <span class="direction-icon">▶</span>
                        <span class="list-content-text">{{ trans.category }}의 {{ trans.percentage}}%를 {{ trans.target }}로 전환</span>
                        <div style="display:inline-block; float: right; margin-top:2.7vh" v-if="select==trans.index && listKind=='trans'">
                            <img style="height:4vh;" src="@/assets/editBtn.png">
                            <img style="height:4vh; margin:0vh 1vw" src="@/assets/deleteBtn.png">
                        </div>
                    </div>
                </div>
            </div>
            <div class = "line"></div>
            <div class="list-box increse-box" id="add-increase-box">
                감축
                <button style="height:4vh; width:4vh; float:right; background:none; border:none; font-size:3rem;color:#3DC984">+</button>
                <div class="list-content-group">
                    <div class="list-content" v-for = "increas in increasList " v-on:mouseover="hoverTarget(increas)" v-on:mouseleave="leaveTarget()">
                        <span class="direction-icon">▶</span>
                        <span class="list-content-text">{{increas.category}}의 {{increas.percentage}}%를 감축</span>
                        <div style="display:inline-block; float: right; margin-top:2.7vh" v-if="select==increas.index && listKind=='increase'">
                            <img style="height:4vh;" src="@/assets/editBtn.png">
                            <img style="height:4vh; margin:0vh 1vw" src="@/assets/deleteBtn.png">
                        </div>
                    </div>  
                </div>
            </div>
            <button class="clickbtn" id="target-save-btn" @click="clickSaveTarget()">저장하기</button>
        </div>
    </div>
        

</template>

<script>
import {ref} from 'vue'
import { useStore } from 'vuex'
    export default {
        name :"openTargetPopup",
        components:{
        },
        setup(){
            const store = useStore()
            var transList=[
                {index:0, category:'전력사용', percentage: 30, target: "태양열 에너지"},
                {index:1, category:'전력사용', percentage: 30, target: "태양열 에너지"},
                {index:2, category:'전력사용', percentage: 30, target: "태양열 에너지"},
                {index:3, category:'전력사용', percentage: 30, target: "태양열 에너지"},
            ]
            var increasList=[
                {index:0, category:'전력사용', percentage: 30},
                {index:1, category:'전력사용', percentage: 30},
                {index:12, category:'전력사용', percentage: 30}
            ]
            const clickSaveTarget = () => {
                console.log('open')
            }
            var select =ref(-1)
            var listKind = ref('')
            const hoverTarget=(value)=>{
                select.value = value.index
                if (value.target == null){
                    listKind.value = 'increase'
                }
                else{
                    listKind.value = 'trans'
                }
            }
            const leaveTarget=()=>{
                select.value = -1
            }
            const closeAddTarget=()=>{
                store.commit('closeAddTarget')
            }
            return{
                transList,
                increasList,
                clickSaveTarget,
                select,
                listKind,
                hoverTarget,
                leaveTarget,
                closeAddTarget
            }
        }
    }
</script>

<style>
.popup-background{
    width:85vw;
    height:100vh;
    background:rgba(43, 42, 42, 0.3);
    
}
.popup-frame{
    margin:auto;
    width:70vw;
    padding:5vh 3vw 8vh 3vw;
    height:64vh;
    margin-top:12vh;
}
#add-trans-box{
    margin-top:2vh;
    width:34vw
}
#add-increase-box{
    margin-top:2vh;
    width:27vw;
}
.close-btn{
    float:right;
    font-size:2rem;
    background: none;
    border:none;
}
.close-btn:hover{
    cursor: pointer;
}
#target-save-btn{
    margin-top:2vh;
    width:inherit;
    height:6vh;
}
</style>
