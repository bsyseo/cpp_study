import { defineComponent, h, PropType, ref, computed } from 'vue'
import {useStore} from 'vuex'
import { Bar } from 'vue-chartjs'
import axios from 'axios'
import {
  Chart as ChartJS,
  Title,
  Tooltip,
  Legend,
  BarElement,
  CategoryScale,
  LinearScale,
  Plugin
} from 'chart.js'

ChartJS.register(Title , Tooltip, Legend, BarElement, CategoryScale, LinearScale)

export default defineComponent({
  name: 'BarChart',
  components: {
    Bar
  },
  props: {
    chartId: {
      type: String,
      default: 'bar-chart'
    },
    width: {
      type: Number,
      default:900 
    },
    height: {
      type: Number,
      default: 100
    },
    cssClasses: {
      default: '',
      type: String
    },
    styles: {
      type: Object as PropType<Partial<CSSStyleDeclaration>>,
      default: () => {}
    },

    plugins: {
      type: Array as PropType<Plugin<'bar'>[]>,
      default: () => []
    },
    
  },
  setup(props) {
    var store = useStore()
    //날짜 그룹명
    var user_group = computed(()=> store.state.user_group)
    var selected_company = computed(()=> store.state.insight_selected_company)

    var now = new Date();	// 현재 날짜 및 시간
    var year = now.getFullYear()	// 년도

    //서버
    var server_total_data = [20,50,60,40,20,30,50,50,40,20,30,60]

    var user = computed(()=>store.state.getTotalLastData).value //작년 총 탄소 배출량
    var server_targetTotal_data =computed(()=>store.state.getTargetData).value //목표량

    console.log(server_targetTotal_data)

    for(var i=0; i<server_total_data.length; i++){
      user = server_total_data[i] + user
    }

    const config = {
        headers:{
            Authorization:"Bearer"+" "+store.state.accessToken,
            "Content-Type": "text/html; charset=euc-kr",
        }
    }

    const chartData = {
      labels: [
        '감축목표량', '사용자설정량',
      ],
      datasets: [
        {
          label : 'sbti',
          backgroundColor: ['#2A565B','#FF7E7E'],
          borderRadius:10,
          data: [user - server_targetTotal_data , user],
          barThickness:20,
        },
      ]
    }

    const chartOptions = {
      indexAxis: 'y' as const,
      responsive: true,
      maintainAspectRatio: false,
      plugins:{
        legend: {
          display:false,
          position:'top' as const,
          align	: 'end' as const,
          labels : {
            padding: 30,
            usePointStyle: true,
            boxWidth:20,
            boxHeight:10,
            color:'#223354'
          }

        },
      },
      ticks: {
        minRotation: 80, // x축 값의 회전 각도를 설정할 수 있어요.
        padding: 5, // x축 값의 상하 패딩을 설정할 수 있어요.
      },
      scales:{
        x:{
          display:false,
        },
        y:{
          display:false,
        },
      }
    }

    return () =>
      h(Bar, {
        chartData,
        chartOptions,
        chartId: props.chartId,
        width: props.width,
        height: props.height,
        cssClasses: props.cssClasses,
        styles: props.styles,
        plugins: props.plugins,
      })
  }
})
